#include "ListFactory.hpp"
#include "ListData.hpp"
#include "ListLink.hpp"
#include "ListPage.hpp"

ListFactory::ListFactory() {}
ListFactory::~ListFactory() {}
Page *ListFactory::createPage(const std::string &title,const std::string &author) {
  return new ListPage(title, author);
}

Link *ListFactory::createLink(const std::string &name, const std::string &url) {
  return new ListLink(name, url);
}

Data *ListFactory::createData(const std::string &name) {
  return new ListData(name);
}
