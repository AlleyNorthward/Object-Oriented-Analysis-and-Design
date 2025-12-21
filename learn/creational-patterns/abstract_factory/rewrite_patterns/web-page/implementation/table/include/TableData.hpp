#ifndef TABLE_DATA_H
#define TABLE_DATA_H

#include "Data.hpp"
#include <string>

class TableData : public Data {

public:
  TableData(const std::string &name);
  ~TableData();
  const std::string toHTML() const;

private:
  TableData(const TableData &) = delete;
  TableData &operator=(const TableData &) = delete;
  TableData(TableData &&) = delete;
  TableData &operator=(TableData &&) = delete;
};

#endif
