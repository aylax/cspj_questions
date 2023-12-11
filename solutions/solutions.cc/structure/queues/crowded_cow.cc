// --------------------------------------------------------
// File: 拥挤的奶牛问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 0  // 1: Open, 0: Close
#endif

struct cow;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using value = int;
using array = std::vector<cow>;
using deque = std::deque<usize>;

// --------------------------------------------------------
// 定义对象
struct cow {
  usize x;  // x pos
  value h;  // height
  int hit;  // 命中次数
};

// --------------------------------------------------------
// Fn: 拥挤的奶牛问题
// 题解: 滑动窗口思路:
// Tip: 共滑动两次, 分别从右往左和从左往右滑动
// 两次都包含某个索引值, 则输出该索引
void crowded_cow() {
#if _TESTDATA_
  // set testdata/xxx.in -> stdin
  freopen("./testdata/crowded_cow.in", "r", stdin);
#endif

  usize n, k;  // 元素个数 n, 距离 k
  std::cin >> n >> k;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i].x >> arr[i].h;
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  // 升序排列
  auto cmp = [](cow &a, cow &b) { return a.x < b.x; };
  std::sort(arr.begin(), arr.end(), cmp);

  deque win;  // 窗口队列, 降序排列

  // 移动窗口, 并调整最值
  auto movewin = [&k, &arr](deque &win, usize index, auto cmp) {
    // 超出搜寻范围
    auto outof_range = [&k](cow &a, cow &b) {
      return !(std::abs(a.x - b.x) <= k);
    };
    // 弹出窗口中所有不符合 cmp(win[back],arr[index]) 的元素
    while (!win.empty() && cmp(arr[win.back()], arr[index])) {
      win.pop_back();
    }

    // arr[index] 元素的索引 index 放入窗口
    win.push_back(index);

    // 保持窗口宽度: xmax - xmin = K
    while (!win.empty() && outof_range(arr[win.front()], arr[index])) {
      win.pop_front();
    }
  };

  // 寻找符合条件的奶牛
  auto findcow = [&k, &arr, &movewin](deque &win, usize index) {
    auto pop_all_small = [](cow &a, cow &b) { return a.h < b.h; };
    movewin(win, index, pop_all_small);
    if (!win.empty() && arr[win.front()].h >= 2 * arr[index].h) {
      arr[index].hit += 1;  // 符合条件命中, 次数加一
    }
  };

  // 从左往右循环移动窗口, 并记录符合条件的值
  for (usize i = 0; i < n; i++) {
    findcow(win, i);
  }

  // 清空窗口
  win.clear();

  // 从右往左循环移动窗口, 并记录符合条件的值
  for (usize i = n - 1; i > 0; i--) {
    findcow(win, i);
  }

  // 计算符合条件的数量
  usize ans = 0;
  for (usize i = 0; i < n; i++) {
    if (arr[i].hit == 2) {
      ans += 1;
    }
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  crowded_cow();
  return 0;
}