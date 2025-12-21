#include "TableFactory.hpp"
#include "TableData.hpp"
#include "TableLink.hpp"
#include "TablePage.hpp"
#include <string>

TableFactory::TableFactory() {}
TableFactory::~TableFactory() {}
Page *TableFactory::createPage(const std::string &title,
                               const std::string &author) {
  return new TablePage(title, author);
}

Link *TableFactory::createLink(const std::string &name,
                               const std::string &url) {
  return new TableLink(name, url);
}

Data *TableFactory::createData(const std::string &name) {
  return new TableData(name);
}
