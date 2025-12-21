#include <cstdint>
#include <string>
#include <array>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <iomanip>

// ---------- 接口 ----------
struct IRegister {
    virtual ~IRegister() = default;
    virtual std::string name() const = 0;
    virtual unsigned width_bits() const = 0;
    // 以 64-bit 为统一外壳，超出部分会被截断
    virtual uint64_t read64() const = 0;
    virtual void write64(uint64_t v) = 0;
};

// ---------- 通用寄存器（GPR）实现（底层用 64-bit storage） ----------
class GPR : public IRegister {
public:
    GPR(std::string n, unsigned bits = 64) : _name(std::move(n)), _width(bits), _storage(0) {
        if (!(bits==8 || bits==16 || bits==32 || bits==64)) throw std::invalid_argument("width must be 8/16/32/64");
    }

    std::string name() const override { return _name; }
    unsigned width_bits() const override { return _width; }

    uint64_t read64() const override { return _storage & mask(_width); }
    void write64(uint64_t v) override { _storage = v & mask(_width); }

    // 便捷函数：按子宽度读取/写入（x86 风格：低位和高 8 位）
    uint8_t read8_low() const  { return static_cast<uint8_t>( _storage & 0xFFu ); }
    void write8_low(uint8_t v) { _storage = (_storage & ~0xFFull) | (uint64_t(v) & 0xFFull); }

    // 高 8 位（例如 AH）位于 bits [8..15]
    uint8_t read8_high() const { return static_cast<uint8_t>( (_storage >> 8) & 0xFFu ); }
    void write8_high(uint8_t v) { _storage = (_storage & ~(0xFFull << 8)) | ((uint64_t(v) & 0xFFull) << 8); }

    uint16_t read16() const { return static_cast<uint16_t>(_storage & 0xFFFFu); }
    void write16(uint16_t v) { _storage = (_storage & ~0xFFFFull) | (uint64_t(v) & 0xFFFFull); }

    uint32_t read32() const { return static_cast<uint32_t>(_storage & 0xFFFFFFFFu); }
    void write32(uint32_t v) { _storage = (_storage & ~0xFFFFFFFFull) | (uint64_t(v) & 0xFFFFFFFFull); }

private:
    std::string _name;
    unsigned _width; // 8/16/32/64
    uint64_t _storage; // always stored in 64-bit slot; real width = _width

    static uint64_t mask(unsigned bits) {
        if (bits >= 64) return ~0ULL;
        return (bits == 0) ? 0ULL : ((1ULL << bits) - 1ULL);
    }
};

// ---------- 段寄存器（结构化） ----------
struct SegmentDesc {
    uint16_t selector = 0;
    uint64_t base = 0;
    uint32_t limit = 0;
    uint8_t access = 0; // access rights byte
};

class SegmentRegister : public IRegister {
public:
    SegmentRegister(std::string n) : _name(std::move(n)) {}
    std::string name() const override { return _name; }
    unsigned width_bits() const override { return sizeof(SegmentDesc) * 8; } // not meaningful for x86, just illustrative

    uint64_t read64() const override {
        // 将 selector/base/limit/access 简单地打包成 64-bit（仅示意）
        uint64_t v = descriptor.selector;
        v |= (uint64_t(descriptor.access) << 16);
        v |= (uint64_t(descriptor.limit) << 24);
        // base 32 bits 放高位（截断）
        v |= (uint64_t(descriptor.base & 0xFFFFFFFFULL) << 56); // 只示意，不严谨
        return v;
    }
    void write64(uint64_t v) override {
        descriptor.selector = uint16_t(v & 0xFFFFu);
        descriptor.access = uint8_t((v >> 16) & 0xFFu);
        descriptor.limit = uint32_t((v >> 24) & 0xFFFFFFFFu);
        // base 取高位示意
        descriptor.base = (v >> 56) & 0xFFu;
    }
    SegmentDesc descriptor;
private:
    std::string _name;
};

// ---------- 寄存器文件：管理别名/查表 ----------
class RegisterFile {
public:
    RegisterFile() {
        // 例：初始化 16 个通用寄存器（64-bit）
        const char* names64[16] = {"RAX","RBX","RCX","RDX","RSI","RDI","RBP","RSP","R8","R9","R10","R11","R12","R13","R14","R15"};
        for (int i=0;i<16;i++) {
            gprs[i] = std::make_unique<GPR>(names64[i], 64);
            nameToGPR[names64[i]] = gprs[i].get();
        }

        // 别名映射（示意）
        nameToAlias["EAX"] = { gprs[0].get(), 32, 0 }; // lower 32 bits of RAX
        nameToAlias["AX"]  = { gprs[0].get(), 16, 0 };
        nameToAlias["AL"]  = { gprs[0].get(), 8, 0 };
        nameToAlias["AH"]  = { gprs[0].get(), 8, 8 }; // high byte of low 16-bit

        // 段寄存器示意
        ds = std::make_unique<SegmentRegister>("DS");
        nameToSeg["DS"] = ds.get();
    }

    // 直接按 64-bit 读写全寄存器
    uint64_t readGPR64(const std::string& n) const {
        auto it = nameToGPR.find(n);
        if (it == nameToGPR.end()) throw std::runtime_error("no such gpr");
        return it->second->read64();
    }
    void writeGPR64(const std::string& n, uint64_t v) {
        auto it = nameToGPR.find(n);
        if (it == nameToGPR.end()) throw std::runtime_error("no such gpr");
        it->second->write64(v);
    }

    // 按别名读写（EAX/AX/AL/AH）
    uint64_t readByName(const std::string& n) const {
        auto it = nameToAlias.find(n);
        if (it != nameToAlias.end()) {
            const AliasInfo &a = it->second;
            uint64_t whole = a.reg->read64();
            uint64_t masked = (whole >> a.shift) & ((1ULL << a.bits) - 1ULL);
            return masked;
        }
        // fallback check GPR
        auto it2 = nameToGPR.find(n);
        if (it2 != nameToGPR.end()) return it2->second->read64();
        // segment?
        auto it3 = nameToSeg.find(n);
        if (it3 != nameToSeg.end()) return it3->second->read64();

        throw std::runtime_error("unknown register name");
    }

    void writeByName(const std::string& n, uint64_t v) {
        auto it = nameToAlias.find(n);
        if (it != nameToAlias.end()) {
            const AliasInfo &a = it->second;
            // 先读原值，清相应区，再写回
            uint64_t whole = a.reg->read64();
            uint64_t clearMask = ~(((1ULL << a.bits) - 1ULL) << a.shift);
            whole = whole & clearMask;
            uint64_t inserted = (v & ((1ULL << a.bits) - 1ULL)) << a.shift;
            a.reg->write64(whole | inserted);
            return;
        }
        auto it2 = nameToGPR.find(n);
        if (it2 != nameToGPR.end()) { it2->second->write64(v); return; }
        auto it3 = nameToSeg.find(n);
        if (it3 != nameToSeg.end()) { it3->second->write64(v); return; }

        throw std::runtime_error("unknown register name");
    }

private:
    struct AliasInfo {
        GPR* reg;
        unsigned bits;
        unsigned shift; // 0 for low, 8 for AH, etc
    };

    std::array<std::unique_ptr<GPR>, 16> gprs;
    std::unordered_map<std::string, GPR*> nameToGPR;
    std::unordered_map<std::string, AliasInfo> nameToAlias;
    std::unique_ptr<SegmentRegister> ds;
    std::unordered_map<std::string, SegmentRegister*> nameToSeg;
};
 
// ---------- 简单演示 ----------
int main() {
    RegisterFile rf;
    rf.writeByName("RAX", 0x1122334455667788ULL);
    std::cout << std::hex << rf.readByName("RAX") << "\n";
    std::cout << "EAX=" << rf.readByName("EAX") << "\n";
    std::cout << "AX=" << rf.readByName("AX") << "\n";
    std::cout << "AL=" << rf.readByName("AL") << "\n";
    std::cout << "AH=" << rf.readByName("AH") << "\n";

    rf.writeByName("AL", 0x99);
    std::cout << "After AL=0x99, RAX=" << rf.readByName("RAX") << "\n";
    return 0;
}












