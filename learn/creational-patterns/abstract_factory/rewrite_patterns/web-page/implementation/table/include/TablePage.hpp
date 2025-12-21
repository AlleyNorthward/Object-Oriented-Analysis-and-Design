#ifndef _TABLE_PAGE_H
#define _TABLE_PAGE_H
#include "Page.hpp"
#include <string>

class TablePage : public Page {
public:
  TablePage(const std::string &title, const std::string &author);
  ~TablePage();
  const std::string toHTML() const;

private:
  TablePage(const TablePage &) = delete;
  TablePage &operator=(const TablePage &) = delete;
  TablePage(TablePage &&) = delete;
  TablePage &operator=(TablePage &&) = delete;
};

#endif
