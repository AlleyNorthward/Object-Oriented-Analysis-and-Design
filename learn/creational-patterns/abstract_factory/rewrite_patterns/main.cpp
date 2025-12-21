#include "Data.hpp"
#include "Factory.hpp"
#include "Link.hpp"
// #include "ListFactory.hpp"
#include "Page.hpp"
#include "TableFactory.hpp"

using namespace std;

int main(int args, char *argv[]) {
  Factory *factory = nullptr;
  // factory = new ListFactory();
  factory = new TableFactory();

  Link *washington_post = factory->createLink(
      "The Washington Post", "https://www.washingtonpost.com/");

  Link *new_york_times =
      factory->createLink("The NewYork Times", "https://www.nytimes.com/");

  Link *financial_times =
      factory->createLink("The Financial Times", "https://www.ft.com/");

  Data *newspaper = factory->createData("newspaper");
  newspaper->add(washington_post);
  newspaper->add(new_york_times);
  newspaper->add(financial_times);

  Link *yahoo = factory->createLink("Yahoo!", "https://www.yahoo.com/");
  Link *google = factory->createLink("Google", "https://www.google.com/");

  Data *search_engine = factory->createData("Search engine");

  search_engine->add(yahoo);
  search_engine->add(google);
  
  Link* xiangbei = factory->createLink("xiangbei", "https://www.yahoo.com");
  Link* enheng = factory->createLink("enheng", "hppps://www.123.com");

  Data* heiheiheiha = factory->createData("1234");

  heiheiheiha->add(xiangbei);
  heiheiheiha->add(enheng);

  Page *link_page = factory->createPage("LinkPage", "James Smith");

  link_page->add(newspaper);
  link_page->add(search_engine);
  link_page->add(heiheiheiha);
  link_page->output();

  delete link_page;
  delete factory;
}
