// --------------------------------------------------------
// File: 货仓选址问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
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
// Fn: 货仓选址问题
// 题解: 二分法思想
// 货仓应该在排好序的列表的中间位置
void warehouse_addr() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/warehouse_addr.in", "r", stdin);
#endif

  usize n;
  std::cin >> n;

  array arr(n);

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  // 升序排序
  // Lambda: Compare(a, b)
  auto cmp = [](value &a, value &b) -> bool { return a < b; };
  std::sort(arr.begin(), arr.end(), cmp);

  value median = arr[n / 2];  // 中位数

  long ans = 0;  // 最短距离求和

  for (usize i = 0; i < n; i++) {
    ans += std::abs(arr[i] - median);
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  warehouse_addr();
  return 0;
}