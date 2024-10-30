#include "scheduler.hpp"

#include <iostream>

auto main() -> int {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  TaskScheduler scheduler(4);

  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; },
                std::time(nullptr) + 5);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 0);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 1);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 2);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 3);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 4);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 5);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 6);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 7);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 8);
  scheduler.Add([] { std::cout << "Hello, world!" << std::endl; }, 9);

  return 0;
}
