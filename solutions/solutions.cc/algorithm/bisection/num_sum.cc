// --------------------------------------------------------
// File: 数求和问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 0  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名
using value = int;
using usize = int;
using array = std::vector<value>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: Binary Search 二分查找, 数组升序排列
// Tip: 从索引1开始
usize binary_search(array &arr, value &val) {
  // Lambda: Binary Fn 二分查找迭代实现
  auto binfn = [](array &arr, value &val, usize begin, usize end) {
    usize bin, low = begin, high = end;

    while (low <= high) {
      bin = (low + high) >> 1;  // 更新二分查找点
      if (val == arr[bin]) {
        return bin;
      } else if (val < arr[bin]) {
        high = bin - 1;
      } else {
        low = bin + 1;
      }
    }

    return 0;
  };

  // Start Binary Search
  return binfn(arr, val, 1, arr.size() - 1);
};

// --------------------------------------------------------
// Fn: 数求和问题
// 题解: 二分查找
void num_sum() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/num_sum.in", "r", stdin);
#endif

  usize n;
  std::cin >> n;

  array arr(n + 1);
  // 录入n个数，录入前已排好序 (升序排列)
  for (usize i = 1; i < n + 1; i++) {
    std::cin >> arr[i];
  }

  value k, s;

  std::cin >> k >> s;

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  value x = s - k;

  // 二分查找元素
  usize index = binary_search(arr, x);
  auto ans = (index == 0) ? "No" : "Yes";
  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  num_sum();
  return 0;
}