#ifndef TABLE_FACTORY_HPP
#define TABLE_FACTORY_HPP

#include "Factory.hpp"
#include <string>

class TableFactory : public Factory {

public:
  TableFactory();
  ~TableFactory();
  Page *createPage(const std::string &title, const std::string &author);
  Link *createLink(const std::string &name, const std::string &url);
  Data *createData(const std::string &name);

private:
  TableFactory(const TableFactory &) = delete;
  TableFactory &operator=(const TableFactory &) = delete;
  TableFactory(TableFactory &&) = delete;
  TableFactory &operator=(TableFactory &&) = delete;
};

#endif
