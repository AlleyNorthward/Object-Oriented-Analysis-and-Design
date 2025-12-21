#ifndef _TABLE_LINK_H
#define _TABLE_LINK_H

#include "Link.hpp"
#include <string>

class TableLink : public Link {

public:
  TableLink(const std::string &name, const std::string &url);
  ~TableLink();
  const std::string toHTML() const;

private:
  TableLink(const TableLink &) = delete;
  TableLink &operator=(const TableLink &) = delete;
  TableLink(TableLink &&) = delete;
  TableLink &operator=(TableLink &&) = delete;
};

#endif
