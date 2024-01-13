// --------------------------------------------------------
// File: 巴什博弈问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
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
// cmap: 巴什博弈问题
// 题解: 对策论思想，最先进入必胜状态
// 分析:
// 首先我们定义奇异局势为：选手面对奇异局势时必输。

// 所以，对于博弈游戏的分析转化为寻找奇异局势。
void bash_game() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/bash_game.in", "r", stdin);
#endif

  int n, k;  // n枚石子, 每次最多取k个
  std::cin >> n >> k;

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif
  bool ans = n % (k + 1) != 0;

  std::cout << (ans ? "Alice" : "Blob") << "\n";
}

// --------------------------------------------------------
// cmap: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  bash_game();
  return 0;
}