#ifndef LIST_PAGE_HPP
#define LIST_PAGE_HPP

#include "Page.hpp"
#include <string>

class ListPage : public Page {
public:
  ListPage(const std::string &title, const std::string &author);
  ~ListPage();
  const std::string toHTML() const;

private:
  ListPage(const ListPage &) = delete;
  ListPage &operator=(const ListPage &) = delete;
  ListPage(ListPage &&) = delete;
  ListPage &operator=(ListPage &&) = delete;
};
#endif
