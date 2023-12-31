// --------------------------------------------------------
// File: 单调队列问题
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
using deque = std::deque<usize>;
using array = std::vector<value>;

// --------------------------------------------------------
// 定义答案对象
struct answer {
  value maxval;  // 窗口内最大值
  value minval;  // 窗口内最小值
};

// --------------------------------------------------------
// Fn: 单调队列问题
// 题解: 滑动窗口思路
void mono_queue() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/mono_queue.in", "r", stdin);
#endif

  usize n, k;  // 元素个数 n, 片段长度 m
  std::cin >> n >> k;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  std::vector<answer> ans;  // 窗口答案最值
  deque maxwin;             // 窗口队列, 降序排列
  deque minwin;             // 窗口队列, 升序排列

  // Lambda: 移动窗口, 并调整最值
  auto movewin = [&k, &arr](deque &win, usize i, auto cmp) {
    // Lambda: 超出搜寻范围
    auto is_outside = [&k](usize a, usize b) {
      if (a < b) std::swap(a, b);
      return !(a - b < k);
    };
    // 弹出窗口中所有不符合 cmp(win[back],arr[i]) 的元素
    while (!win.empty() && cmp(arr[win.back()], arr[i])) {
      win.pop_back();
    }

    // arr[i] 元素的索引 i 放入窗口
    win.push_back(i);

    // 保持窗口宽度: Len = K
    while (!win.empty() && is_outside(i, win.front())) {
      win.pop_front();
    }
  };

  // Lambda: 弹出所有小于b的元素
  auto pop_all_small = [](value a, value b) { return a < b; };
  // Lambda: 弹出所有大于b的元素
  auto pop_all_large = [](value a, value b) { return a > b; };

  // 从左往右循环移动窗口, 并记录符合条件的值
  for (usize i = 0; i < n; i++) {
    movewin(maxwin, i, pop_all_small);
    movewin(minwin, i, pop_all_large);

    if (i >= k - 1) {  // 每偏移一次, 就记录窗口最值
      value maxval = arr[maxwin.front()];
      value minval = arr[minwin.front()];
      ans.push_back({maxval, minval});
    }
  }

  // 打印各个窗口最值
  for (usize i = 0; i < ans.size(); i++) {
    std::cout << ans[i].maxval << " ";
    std::cout << ans[i].minval << "\n";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  mono_queue();
  return 0;
}