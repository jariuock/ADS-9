// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include "tree.h"
using namespace std;

int main() {
    cout << "n\tgetAllPerms(ms)\tgetPerm1(ms)\tgetPerm2(ms)" << endl;

 for (int n = 2; n <= 10; ++n) {
     vector<char> input(n);
     iota(input.begin(), input.end(), '1');

     PMTree tree(input);

     int perm_count = 1;
     for (int i = 2; i <= n; ++i)
         perm_count *= i;

     int num = rand() % perm_count + 1;

     auto t1 = chrono::high_resolution_clock::now();
     auto all = getAllPerms(tree);
     auto t2 = chrono::high_resolution_clock::now();
     double t_all = chrono::duration<double, std::milli>(t2 - t1).count();

     t1 = chrono::high_resolution_clock::now();
     auto p1 = getPerm1(tree, num);
     t2 = chrono::high_resolution_clock::now();
     double t_p1 = chrono::duration<double, std::milli>(t2 - t1).count();

     t1 = chrono::high_resolution_clock::now();
     auto p2 = getPerm2(tree, num);
     t2 = chrono::high_resolution_clock::now();
     double t_p2 = chrono::duration<double, std::milli>(t2 - t1).count();

     cout << n << "\t" << t_all << "\t\t" << t_p1 << "\t\t" << t_p2 << endl;
 }
  return 0;
}
