//
// Created by jesse on 1/16/24.
//

#include "FileSearch.hpp"
#include <atomic>
#include <cstdint>
#include <fstream>
#include <future>
#include <iostream>
#include <mutex>
#include <string>

static std::mutex mutex;

std::atomic_uint64_t remind;
uint64_t totalNum;

void FileSearch::fileFilter(const std::filesystem::directory_entry &entity,
                            std::string_view searchContent) noexcept {
  if (entity.is_regular_file() && FileSearch::_isFileText(entity.path())) {
    std::ifstream stream(entity.path());
    std::string line;
    while (std::getline(stream, line)) {
      if (line.find(searchContent) != std::string::npos) {
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << entity.path() << std::endl;
        break;
      }
    }
    const int64_t remindNum = remind.fetch_sub(1);
    const double percentage = (static_cast<double>(totalNum) - remindNum) / totalNum;
    std::cout << "Searching - " << std::to_string(percentage * 100) << "%\r";
    std::cout.flush();
  }
}

void FileSearch::doSearch() const noexcept {
  std::vector<std::unique_ptr<std::packaged_task<void()>>> executables;
  for (const auto &entity : std::filesystem::recursive_directory_iterator(path)) {
    executables.push_back(std::make_unique<std::packaged_task<void()>>([entity, this]() {
      FileSearch::fileFilter(entity, this->searchContent);
    }));
  }

  totalNum = executables.size();
  remind = executables.size();

  for (auto &task : executables) {
    std::future<void> future = task->get_future();
    threadPool->post(*task);
    future.get();
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