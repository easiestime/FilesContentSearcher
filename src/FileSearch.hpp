#ifndef __file_content_search_file_search__
#define __file_content_search_file_search__

/// @brief file search main class
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
class FileSearch {
public:
  /**
      @brief default construct for FileSearch class
      @param _path: sandbox path
      @param _content: search content
  */
  FileSearch(std::filesystem::path _path, std::string_view _content)
      : path(_path), searchContent(_content) {
  }

  /**
  @brief main function for search
  */
  void doSearch() {
    for (const auto &entity : std::filesystem::recursive_directory_iterator(path)) {
      if (entity.is_regular_file() && _isFileText(entity.path())) {
        std::ifstream stream(entity.path());
        std::string line;
        while (std::getline(stream, line)) {
          if (line.find(this->searchContent) != std::string::npos) {
            std::cout << entity.path() << std::endl;
            break;
          }
        }
      }
    }
  }

private:
  std::filesystem::path path;
  std::string_view searchContent;
  bool _isFileText(const std::filesystem::path &_path) {
    std::ifstream stream(_path);
    unsigned char c;
    while (stream >> c) {
      if (std::isspace(c) == 0 && std::isprint(c) == 0) {
        return false;
      }
    }
    return true;
  }
};

#endif