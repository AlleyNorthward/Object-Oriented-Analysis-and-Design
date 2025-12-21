#ifndef LIST_FACTORY_HPP
#define LIST_FACTORY_HPP

#include "Factory.hpp"
#include <string>

class ListFactory : public Factory {
public:
  ListFactory();
  ~ListFactory();

  Page *createPage(const std::string &title, const std::string &author);
  Link *createLink(const std::string &name, const std::string &url);
  Data *createData(const std::string &name);

private:
  ListFactory(const ListFactory &) = delete;
  ListFactory &operator=(const ListFactory &) = delete;
  ListFactory(ListFactory &&) = delete;
  ListFactory &operator=(ListFactory &&) = delete;
};

#endif
