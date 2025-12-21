#include "Page.hpp"
#include "Item.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>

Page::Page(const std::string &title, const std::string &author)
    : title(title), author(author) {}

Page::~Page() {
  for (Item *content : contents) {
    delete content;
  }
  contents.clear();
}

void Page::add(Item *item) { contents.push_back(item); }

void Page::output() const {
  const std::string file_name = title + ".html";
  std::ofstream writer(file_name);

  if (!writer) {
    std::cerr << "创立失败:" << file_name << std::endl;
    return;
  }

  writer << toHTML();
  std::cout << file_name << "已经被创建了." << std::endl;

  const auto output_path = std::filesystem::current_path() / file_name;
  std::cout << "输出文件:" << output_path << std::endl;
}
