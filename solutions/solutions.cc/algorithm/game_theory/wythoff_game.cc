// --------------------------------------------------------
// File: 威佐夫博弈问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <cmath>
#include <iostream>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 0  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名

// --------------------------------------------------------
// 定义节点对象

// --------------------------------------------------------
// Fn: 威佐夫博弈问题
// 题解: 对策论思想，寻找奇异局势
// 分析:
// 首先我们定义奇异局势为：选手面对奇异局势时必输。
// 所以，对于博弈游戏的分析转化为寻找奇异局势。
// 先手必败局势: (0, 0), (1, 2) (3, 5), (4, 7) ...
// 观察可以找出规律:
// 1) 每一组元素的差值是递增的, 0-0=0, 2-1=1, 5-3=2, ...
// 2) 每一组元素的第一个值 = 差值 * PHI(黄金比例1.618...)
void wythoff_game() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/wythoff_game.in", "r", stdin);
#endif

  int a, b;  // 第一堆a枚石子, 第二堆b枚石子
  std::cin >> a >> b;

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  if (a > b) std::swap(a, b);

  // 计算黄金比例phi值
  auto phi = (1.0 + std::sqrt(5.0)) / 2.0;
  auto dif = (double)b - a;
  int ret = std::floor(phi * dif);

  std::cout << ((a != ret) ? "Alice" : "Bob") << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  wythoff_game();
  return 0;
}