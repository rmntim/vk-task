#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class TaskScheduler {
public:
  TaskScheduler(std::size_t worker_count);
  ~TaskScheduler();

  void Add(std::function<void()> task, std::time_t timestamp) noexcept;

private:
  struct Task {
    std::time_t timestamp;
    std::function<void()> func;

    Task(std::time_t t, std::function<void()> f)
        : timestamp(t), func(std::move(f)) {}

    bool operator<(const Task &other) const {
      return timestamp > other.timestamp;
    }
  };

  std::priority_queue<Task> tasks;
  std::vector<std::thread> workers;
  std::mutex mutex;
  std::condition_variable condVar;
  bool stop;

  void run() noexcept;
};
