#include "TableLink.hpp"

TableLink::TableLink(const std::string &name, const std::string &url)
    : Link(name, url) {}

TableLink::~TableLink() {}

const std::string TableLink::toHTML() const {
  return "  <td><a href=\"" + url + "\">" + name + "</a></td>\n";
}
