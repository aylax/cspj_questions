// --------------------------------------------------------
// File: 尼姆博弈问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <cmath>
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
using array = std::vector<int>;

// --------------------------------------------------------
// 定义节点对象

// --------------------------------------------------------
// Fn: list xor
// xor: 二进制 位异或 运算
int list_xor(const array& a) {
  int ret = 0;
  for (auto e : a) {
    ret ^= e;
  }
  return ret;
}

// --------------------------------------------------------
// Fn: 尼姆博弈问题
// 题解: 对策论思想，最先进入必胜状态
// 分析:
// 首先我们定义奇异局势为：选手面对奇异局势时必输。
// 所以，对于博弈游戏的分析转化为寻找奇异局势。
// 假设只有3堆石子, 每堆任意数量
// (0, 0, 0) 先手必败, 无子可取
// (0, n, n) 先手必败, 对手模仿自己的操作就行
// 对于 (a, b, c) 局势, 只要保证对手先进入(0, n, n)局势就行
// 问题点现在转化为:
// (a, b, c) 局势下，谁最先能通过取子，让对手进入 (0, n, n)
void nim_game() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/nim_game.in", "r", stdin);
#endif

  int n;  // n堆石子
  std::cin >> n;

  array dn(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> dn[i];
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  int ret = list_xor(dn);
  std::cout << ((ret != 0) ? "Alice" : "Bob") << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const* argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  nim_game();
  return 0;
}