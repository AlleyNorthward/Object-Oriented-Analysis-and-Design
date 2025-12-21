#include "TablePage.hpp"
#include "Item.hpp"
#include <sstream>

TablePage::TablePage(const std::string &title, const std::string &author)
    : Page(title, author) {}

TablePage::~TablePage() {}

const std::string TablePage::toHTML() const {
  std::stringstream buffer;
  buffer << "<html><head><title>" << title << "</title></head><body>"
         << std::endl;
  buffer << "<h1>" << title << "</h1>" << std::endl;
  buffer << "<table width=\"80%\" border=\"3\">" << std::endl;
  for (Item *content : contents) {
    buffer << "<tr>" << content->toHTML() << "</tr>" << std::endl;
  }
  buffer << "</table>" << std::endl;
  buffer << "<hr><address>" << author << "</address>" << std::endl;
  buffer << "</body></html>" << std::endl;
  return buffer.str();
}
