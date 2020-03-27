#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "src/lib/utility.h"

// A demo for creating two threads
// Run this using one of the following methods:
//  1. With bazel: bazel run src/main:vector_of_threads_main
//  2. With plain g++: g++ -std=c++17 -lpthread
//  src/main/vector_of_threads_main.cc  -I ./
int main() {
  const int number_of_threads = 10;
  uint64_t number_of_elements = 1000 * 1000 * 1000;
  uint64_t step = number_of_elements / number_of_threads;
  std::vector<std::future<uint64_t>> tasks;
  std::vector<uint64_t> partial_sums(number_of_threads);

  for (uint64_t i = 0; i < number_of_threads; i++) {
    tasks.push_back(std::async([i, step] {
      uint64_t r = 0;
      for (uint64_t j = i * step; j < (i + 1) * step; j++) {
        r += j;
      }
      return r;
    }));
  }

  uint64_t total = 0;
  for (auto &t : tasks) {
    total += t.get();
  }

  std::cout << "total: " << total << std::endl;

  return 0;
}