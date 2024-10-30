#include "scheduler.hpp"

#include <chrono>

TaskScheduler::TaskScheduler(std::size_t worker_count) : stop(false) {
  for (size_t i = 0; i < worker_count; ++i) {
    workers.emplace_back([this] { this->run(); });
  }
}

TaskScheduler::~TaskScheduler() {
  {
    std::unique_lock<std::mutex> lock(mutex);
    stop = true;
  }
  condVar.notify_all();
  for (auto &worker : workers) {
    worker.join();
  }
}

void TaskScheduler::Add(std::function<void()> task,
                        std::time_t timestamp) noexcept {
  std::unique_lock<std::mutex> lock(mutex);
  tasks.emplace(timestamp, std::move(task));
  condVar.notify_one();
}

void TaskScheduler::run() noexcept {
  while (true) {
    std::unique_lock<std::mutex> lock(mutex);
    if (stop && tasks.empty())
      break;

    if (!tasks.empty()) {
      auto now = std::chrono::system_clock::to_time_t(
          std::chrono::system_clock::now());
      if (tasks.top().timestamp <= now) {
        auto task = tasks.top();
        tasks.pop();
        lock.unlock();
        task.func();
      } else {
        condVar.wait_until(lock, std::chrono::system_clock::from_time_t(
                                     tasks.top().timestamp));
      }
    } else {
      condVar.wait(lock);
    }
  }
}
