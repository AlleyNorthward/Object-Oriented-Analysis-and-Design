#include "ListPage.hpp"
#include "Item.hpp"
#include <sstream>

ListPage::ListPage(const std::string &title, const std::string &author)
    : Page(title, author) {}

ListPage::~ListPage(){}

const std::string ListPage::toHTML() const {
  std::stringstream buffer;
  buffer << "<html><head><title>" << title << "</title></head>" << std::endl;
  buffer << "<body><h1>" << title << "</h1>" << std::endl;
  buffer << "<ul>" << std::endl;
  for (Item *content : contents) {
    buffer << content->toHTML();
  }
  buffer << "</ul>" << std::endl;
  buffer << "<hr><address>" << author << "</address>";
  buffer << "</body></html>" << std::endl;
  return buffer.str();
}
