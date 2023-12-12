// --------------------------------------------------------
// File: 伐木工人问题
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
#define _TESTDATA_ 1  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using value = int;
using array = std::vector<value>;

// --------------------------------------------------------
// Fn: Max 获取最小值
value max(value a, value b) { return a > b ? a : b; }

// --------------------------------------------------------
// Fn: 伐木工人问题
// 题解: 二分查找
void woodcut() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/woodcut.in", "r", stdin);
#endif

  usize n, required;  // 树木数量, 需求木材长度
  std::cin >> n >> required;
  array arr(n);

  // 录入木材高度, 并记录最高的树木高度
  value low = 0, high = 0, bin;
  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i];
    high = max(high, arr[i]);
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  // Lambda: 判段是否达标
  auto gt_or_eq = [&n, &required, &arr](value val) {
    value sum = 0;
    for (usize i = 0; i < n; i++) {
      if (arr[i] > val) sum += (arr[i] - val);
      if (sum >= required) return true;
    }
    return false;
  };

  // 二分法快速缩小查找高度
  while (low <= high) {
    bin = (low + high) >> 1;
    if (gt_or_eq(bin)) {
      low = bin + 1;
    } else {
      high = high - 1;
    }
  }

  std::cout << low - 1 << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  woodcut();
  return 0;
}