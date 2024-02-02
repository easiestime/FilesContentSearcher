#include <gtest/gtest.h>
#include "../src/thread_pool/thread_pool.hpp"
#include "../src/thread_pool/thread_pool_options.hpp"

TEST(e2e, e2e) {
  ASSERT_EQ(42, 42);
}

TEST(e2e, thread_pool) {
  tp::ThreadPoolOptions options;
  options.setThreadCount(std::thread::hardware_concurrency());
  tp::ThreadPool pool(options);

  std::mutex printLock;

  auto executable = [&printLock]() {
    // std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
    std::lock_guard<std::mutex> lock(printLock);
    std::cout << std::this_thread::get_id() << "-"
              << "hello world\n";
  };

  std::vector<std::unique_ptr<std::packaged_task<void()>>> executables;

  for (int a = 0; a < 100; ++a) {
    executables.push_back(std::make_unique<std::packaged_task<void()>>(executable));
  }

  for (auto &task : executables) {
    std::future<void> r = task->get_future();
    pool.post(*task);
    r.get();
  }
}