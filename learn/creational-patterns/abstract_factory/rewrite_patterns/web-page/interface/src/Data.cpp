#include "Data.hpp"

Data::Data(const std::string &name) : Item(name) {}
Data::~Data() {
  for (Item *item : items) {
    delete item;
  }
  items.clear();
}
void Data::add(Item *item) { items.push_back(item); }
