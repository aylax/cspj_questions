// --------------------------------------------------------
// File: N个数中找K个数问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明

// --------------------------------------------------------
// 设定类型别名
using Value = int;
using usize = int;
using array = std::vector<Value>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: Binary Search 二分查找, 数组升序排列
// Tip: 从索引1开始
usize binary_search(array &arr, Value &value) {
  // Lambda: Binary Fn 二分查找迭代实现
  auto binfn = [](array &arr, Value &value, usize begin, usize end) {
    usize bin, low = begin, high = end;

    while (low <= high) {
      bin = (low + high) >> 1;  // 更新二分查找点
      if (value == arr[bin]) {
        return bin;
      } else if (value < arr[bin]) {
        high = bin - 1;
      } else {
        low = bin + 1;
      }
    }

    return 0;
  };

  // Start Binary Search
  return binfn(arr, value, 1, arr.size() - 1);
};

// --------------------------------------------------------
// Fn: N个数中找K个数问题
// 题解: 二分查找
void find_kn() {
  usize n, k;
  std::cin >> n >> k;

  array narr(n + 1);
  // 录入n个数，录入前已排好序 (升序排列)
  for (usize i = 1; i < n + 1; i++) {
    std::cin >> narr[i];
  }

  // 录入k个数
  array karr(k);
  for (usize i = 0; i < k; i++) {
    std::cin >> karr[i];
  }

  // 二分查找元素, 并输出 karr[0]
  usize index = binary_search(narr, karr[0]);
  std::cout << index;

  // 二分查找元素, 并输出 karr[1] ~ karr[k-1]
  for (usize i = 1; i < k; i++) {
    usize index = binary_search(narr, karr[i]);
    std::cout << " " << index;
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  find_kn();
  return 0;
}