#ifndef LIST_LINK_HPP
#define LIST_LINK_HPP

#include "Link.hpp"
#include <string>

class ListLink : public Link {
public:
  ListLink(const std::string &name, const std::string &url);
  ~ListLink();
  const std::string toHTML() const;

private:
  ListLink(const ListLink &) = delete;
  ListLink &operator=(const ListLink &) = delete;
  ListLink(ListLink &&) = delete;
  ListLink &operator=(ListLink &&) = delete;
};

#endif
