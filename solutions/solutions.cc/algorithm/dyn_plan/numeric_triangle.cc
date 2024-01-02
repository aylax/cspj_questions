// --------------------------------------------------------
// File: 数字三角形问题
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
using array = std::vector<int>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: Max 获取最大值
int max(int a, int b) { return a > b ? a : b; }

// --------------------------------------------------------
// Fn: 数字三角形问题
// 题解: 动态规划, 从底部往上回溯
// 状态转移公式:
// dp[y][x] = xs[y][x] + max(dp[y+1][x], dp[y+1][x+1])
void numeric_triangle() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/numeric_triangle.in", "r", stdin);
#endif

  int n;  // n行
  std::cin >> n;

  std::vector<array> xs(n + 1, array(n + 1));
  std::vector<array> dp(n + 1, array(n + 1));

  for (int y = 1; y <= n; y++) {
    for (int x = 1; x <= y; x++) {
      std::cin >> xs[y][x];
    }
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  // 初始化最后一行dp数据
  for (int x = 1; x <= n; x++) {
    dp[n][x] = xs[n][x];
  }

  //   从倒数第二行往前求dp值
  for (int y = n - 1; y >= 1; y--) {
    for (int x = 1; x <= y; x++) {
      int d1 = dp[y + 1][x];
      int d2 = dp[y + 1][x + 1];
      dp[y][x] = xs[y][x] + max(d1, d2);
    }
  }

  int ans = dp[1][1];

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  numeric_triangle();
  return 0;
}