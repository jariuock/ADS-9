// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include "tree.h"

int main() {
  std::cout << "n\tgetAllPerms(ms)\tgetPerm1(ms)\tgetPerm2(ms)" << std::endl;

  // Инициализация генератора случайных чисел
  std::mt19937 rng(static_cast<unsigned int>(
      std::chrono::steady_clock::now().time_since_epoch().count()));

  for (int n = 2; n <= 10; ++n) {
    std::vector<char> input(n);
    std::iota(input.begin(), input.end(), '1');

    PMTree tree(input);

    int perm_count = 1;
    for (int i = 2; i <= n; ++i) {
      perm_count *= i;
    }

    std::uniform_int_distribution<int> dist(1, perm_count);
    int num = dist(rng);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto all = getAllPerms(tree);
    auto t2 = std::chrono::high_resolution_clock::now();
    double t_all = std::chrono::duration<double, std::milli>(t2 - t1).count();

    t1 = std::chrono::high_resolution_clock::now();
    auto p1 = getPerm1(tree, num);
    t2 = std::chrono::high_resolution_clock::now();
    double t_p1 = std::chrono::duration<double, std::milli>(t2 - t1).count();

    t1 = std::chrono::high_resolution_clock::now();
    auto p2 = getPerm2(tree, num);
    t2 = std::chrono::high_resolution_clock::now();
    double t_p2 = std::chrono::duration<double, std::milli>(t2 - t1).count();

    std::cout << n << "\t" << t_all << "\t\t" << t_p1 << "\t\t" << t_p2 << std::endl;
  }
  return 0;
}
