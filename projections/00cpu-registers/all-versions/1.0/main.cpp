#include <cstdint>
#include <array>
#include <string>
#include <unordered_map>
#include <iostream>

class SubRegister {
public:
    SubRegister(uint32_t &parent, unsigned offset_bits, unsigned width_bits)
      : parent_(parent), offset_(offset_bits), width_(width_bits) {
        mask_ = (width_ >= 32) ? 0xFFFFFFFFu : ((1u << width_) - 1u);
    }

    uint32_t get() const {
        return (parent_ >> offset_) & mask_;
    }

    void set(uint32_t v) {
        v &= mask_;
        parent_ = (parent_ & ~(mask_ << offset_)) | (v << offset_);
    }

    // convenience operators
    operator uint32_t() const { return get(); }
    SubRegister& operator=(uint32_t v) { set(v); return *this; }

private:
    uint32_t &parent_;
    unsigned offset_;
    unsigned width_;
    uint32_t mask_;
};

class Flags {
public:
    uint32_t raw = 0;
    enum FlagBits { CF = 0, PF = 2, AF = 4, ZF = 6, SF = 7, TF = 8, IF = 9, DF = 10, OF = 11 };
    bool get(int b) const { return (raw >> b) & 1u; }
    void set(int b, bool v) {
        if (v) raw |= (1u << b); else raw &= ~(1u << b);
    }
};

class RegisterFile {
public:
    std::array<uint32_t, 8> regs32 {};
    Flags eflags;
    uint32_t eip = 0;

    std::unordered_map<std::string, SubRegister> views;

    RegisterFile() {
        views.emplace("EAX", SubRegister(regs32[0], 0, 32));
        views.emplace("ECX", SubRegister(regs32[1], 0, 32));
        views.emplace("EDX", SubRegister(regs32[2], 0, 32));
        views.emplace("EBX", SubRegister(regs32[3], 0, 32));
        views.emplace("ESP", SubRegister(regs32[4], 0, 32));
        views.emplace("EBP", SubRegister(regs32[5], 0, 32));
        views.emplace("ESI", SubRegister(regs32[6], 0, 32));
        views.emplace("EDI", SubRegister(regs32[7], 0, 32));

        views.emplace("AX", SubRegister(regs32[0], 0, 16));
        views.emplace("CX", SubRegister(regs32[1], 0, 16));
        views.emplace("DX", SubRegister(regs32[2], 0, 16));
        views.emplace("BX", SubRegister(regs32[3], 0, 16));
        views.emplace("SP", SubRegister(regs32[4], 0, 16));
        views.emplace("BP", SubRegister(regs32[5], 0, 16));
        views.emplace("SI", SubRegister(regs32[6], 0, 16));
        views.emplace("DI", SubRegister(regs32[7], 0, 16));

        views.emplace("AL", SubRegister(regs32[0], 0, 8));
        views.emplace("CL", SubRegister(regs32[1], 0, 8));
        views.emplace("DL", SubRegister(regs32[2], 0, 8));
        views.emplace("BL", SubRegister(regs32[3], 0, 8));

        views.emplace("AH", SubRegister(regs32[0], 8, 8));
        views.emplace("CH", SubRegister(regs32[1], 8, 8));
        views.emplace("DH", SubRegister(regs32[2], 8, 8));
        views.emplace("BH", SubRegister(regs32[3], 8, 8));
    }

    SubRegister& reg(const std::string &name) {
        return views.at(name);
    }
};

int main(){
    RegisterFile rf;
    rf.reg("EAX") = 0x12345678;
    uint32_t ax = rf.reg("AX");   // 0x5678
    std::cout << std::hex << ax << "\n";
    rf.reg("AH") = 0x9A;          // changes bits 8..15 of EAX
    std::cout << std::hex << rf.reg("EAX").get() << "\n";
    return 0;
}












