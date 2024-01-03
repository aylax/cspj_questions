// --------------------------------------------------------
// File: 传球游戏问题
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
// Fn: 传球游戏问题
// 题解: 动态规划
// 状态转移公式:
// dp[y][x] = dp[y-1][x-1] + dp[y-1][x+1]
void passball_gaming() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/passball_gaming.in", "r", stdin);
#endif

  int n, m;  // n人, m次
  std::cin >> n >> m;

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  std::vector<array> dp(m + 1, array(n + 1, 0));

  dp[0][1] = 1;
  for (int c = 1; c <= m; c++) {
    for (int i = 1; i <= n; i++) {
      // 圆环结构, 保证元素在环内
      int rt = 1 + i % n;
      int lt = 1 + (n + i - 2) % n;
      dp[c][i] = dp[c - 1][rt] + dp[c - 1][lt];
    }
  }

  int ans = dp[m][1];
  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  passball_gaming();
  return 0;
}
