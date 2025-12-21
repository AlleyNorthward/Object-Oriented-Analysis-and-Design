#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>
#include <vector>

class Item;

class Page {
protected:
  const std::string title;
  const std::string author;
  std::vector<Item *> contents;

public:
  Page(const std::string &title, const std::string &author);
  virtual ~Page();
  virtual const std::string toHTML() const = 0;
  void add(Item *item);
  void output() const;
};

#endif
