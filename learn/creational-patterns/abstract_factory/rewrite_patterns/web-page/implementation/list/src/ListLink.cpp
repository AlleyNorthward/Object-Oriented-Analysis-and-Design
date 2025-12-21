#include "ListLink.hpp"
ListLink::ListLink(const std::string &name, const std::string &url)
    : Link(name, url) {}

ListLink::~ListLink() {}

const std::string ListLink::toHTML() const {
  return "  <li><a href=\"" + url + "\">" + name + "</a></li>\n";
}
