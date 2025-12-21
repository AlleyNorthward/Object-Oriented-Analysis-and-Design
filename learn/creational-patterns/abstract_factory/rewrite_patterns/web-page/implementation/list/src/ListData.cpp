#include "ListData.hpp"
#include "Item.hpp"
#include "sstream"
#include <ostream>
#include <sstream>

ListData::ListData(const std::string &name) : Data(name) {}

ListData::~ListData() {}

const std::string ListData::toHTML() const {
  std::stringstream buffer;
  buffer << "<li>" << name << "<ul>" << std::endl;
  for (Item *item : items) {
    buffer << item->toHTML();
  }
  buffer << "</ul></li>" << std::endl;
  return buffer.str();
}
