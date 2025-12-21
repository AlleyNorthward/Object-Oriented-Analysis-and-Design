#ifndef LIST_DATA_HPP
#define LIST_DATA_HPP

#include "Data.hpp"
#include "string"

class ListData : public Data {
public:
  ListData(const std::string &name);
  ~ListData();
  const std::string toHTML() const;

private:
  ListData(const ListData &) = delete;
  ListData &operator=(const ListData &) = delete;
  ListData(ListData &&) = delete;
  ListData &operator=(ListData &&) = delete;
};

#endif
