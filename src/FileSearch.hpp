#ifndef __file_content_search_file_search__
#define __file_content_search_file_search__

/// @brief file search main class
#include <filesystem>
#include <memory>
#include <string_view>
#include <utility>
#include "thread_pool/thread_pool.hpp"
class FileSearch {
public:
  /**
      @brief default construct for FileSearch class
      @param _path: sandbox path
      @param _content: search content
  */
  FileSearch(std::filesystem::path _path, const std::string_view _content)
      : path(std::move(_path)), searchContent(_content) {
    tp::ThreadPoolOptions options;
    options.setThreadCount(std::thread::hardware_concurrency());
    threadPool = std::make_unique<tp::ThreadPool>(options);
  }

  /**
  @brief main function for search
  */
  void doSearch() const noexcept;

private:
  std::filesystem::path path;
  std::string_view searchContent;
  [[nodiscard]] static bool _isFileText(const std::filesystem::path &_path) noexcept;
  static void fileFilter(const std::filesystem::directory_entry &entity,
                         std::string_view searchContent) noexcept;
  std::unique_ptr<tp::ThreadPool> threadPool;
};

#endif