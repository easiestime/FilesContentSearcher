#include <filesystem>
#include <iostream>
#include <stdexcept>
#include "src/FileSearch.hpp"

int main(int argc, char **argv) {
  if (argc == 3) {
    std::filesystem::path _path{argv[1]};
    if (!std::filesystem::is_directory(_path)) {
      throw std::runtime_error("path is not a directory!");
    }
    FileSearch searcher(_path, argv[2]);
    searcher.doSearch();
  } else {
    std::cout << "demo: ./fcsearch directory content \n";
  }
}
