#ifndef LINK_HPP
#define LINK_HPP

#include "Item.hpp"
#include <string>

class Link : public Item {
protected:
  const std::string url;

public:
  Link(const std::string &name, const std::string &url);
  virtual ~Link() = default;

private:
  Link(const Link &) = delete;
  Link &operator=(const Link &) = delete;
  Link(Link &&) = delete;
  Link &operator=(Link &&) = delete;
};
#endif
