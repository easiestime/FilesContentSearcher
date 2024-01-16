//
// Created by jesse on 1/16/24.
//

#include "FileSearch.hpp"

void FileSearch::doSearch() const noexcept {
  for (const auto &entity : std::filesystem::recursive_directory_iterator(path)) {
    if (entity.is_regular_file() && FileSearch::_isFileText(entity.path())) {
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

bool FileSearch::_isFileText(const std::filesystem::path &_path) noexcept {
  std::ifstream stream(_path);
  unsigned char c;
  while (stream >> c) {
    if (std::isspace(c) == 0 && std::isprint(c) == 0) {
      return false;
    }
  }
  return true;
}