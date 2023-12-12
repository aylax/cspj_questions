// --------------------------------------------------------
// File: 连续子序列的最大值问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <deque>
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
using usize = int;
using value = int;
using array = std::vector<value>;
using deque = std::deque<usize>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 连续子序列的最大值问题
// 题解: 滑动窗口思路
void max_subseq() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/max_subseq.in", "r", stdin);
#endif

  usize n, k;  // 元素个数 n, 片段长度 k
  std::cin >> n >> k;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  array ans;  // 各个窗口最大值答案
  deque win;  // 窗口队列, 降序排列

  // Lambda: 移动窗口, 并调整最值
  auto movewin = [&k, &arr](deque &win, usize index, auto cmp) {
    // Lambda: 超出搜寻范围
    auto outof_range = [&k](usize diff) { return !(std::abs(diff) < k); };

    // 弹出窗口中所有不符合 cmp(win[back],arr[index]) 的元素
    while (!win.empty() && cmp(arr[win.back()], arr[index])) {
      win.pop_back();
    }

    // arr[index] 元素的索引 index 放入窗口
    win.push_back(index);

    // 保持窗口宽度: Len = K
    while (!win.empty() && outof_range(index - win.front())) {
      win.pop_front();
    }
  };

  // Lambda: 弹出所有小于b的元素
  auto pop_all_small = [](value a, value b) { return a < b; };

  // 从左往右循环移动窗口, 并记录符合条件的值
  for (usize i = 0; i < n; i++) {
    movewin(win, i, pop_all_small);

    if (i >= k - 1) {  // 每偏移一次, 就记录窗口最值
      ans.push_back(arr[win.front()]);
    }
  }

  // 打印各个窗口最值
  for (usize i = 0; i < ans.size(); i++) {
    std::cout << ans[i] << " ";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  max_subseq();
  return 0;
}