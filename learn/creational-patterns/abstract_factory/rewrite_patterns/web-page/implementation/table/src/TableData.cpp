#include "TableData.hpp"
#include "Item.hpp"
#include <sstream>
#include <string>

TableData::TableData(const std::string &name) : Data(name) {}

TableData::~TableData() {}

const std::string TableData::toHTML() const {
  std::stringstream buffer;
  buffer << "<td><table width=\"100%\" border=\"2\">" << std::endl;
  buffer << "<tr><td bgcolor=\"#00CC00\" align=\"center\" colspan=\""
         << std::to_string(items.size()) << "\"><b>" << name << "</b></td></tr>"
         << std::endl;
  buffer << "<tr>" << std::endl;
  for (Item *item : items) {
    buffer << item->toHTML();
  }
  buffer << "</tr>" << std::endl;
  buffer << "</table></td>" << std::endl;
  return buffer.str();
}
