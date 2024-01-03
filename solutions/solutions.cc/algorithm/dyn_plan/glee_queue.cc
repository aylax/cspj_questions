// --------------------------------------------------------
// File: 合唱队形问题
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
using usize = int;
using value = int;
using array = std::vector<value>;
// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: Max 获取最大值
value max(value a, value b) { return a > b ? a : b; }

// --------------------------------------------------------
// Fn: Min 获取最小值
value min(value a, value b) { return a < b ? a : b; }

// --------------------------------------------------------
// Fn: 合唱队形问题
// 题解: 动态规划
// 状态转移公式:
// FOR k in 1..n-1:
// Let dp[n] = max(dp[n], dp[k] + 1)
void glee_queue() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/glee_queue.in", "r", stdin);
#endif

  usize n;  // n个元素
  std::cin >> n;

  std::vector<value> xs(n + 1);
  for (usize i = 1; i <= n; i++) {
    std::cin >> xs[i];
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  std::vector<array> dp(2, array(n + 1, 1));

  // 从左往中间递增序列
  for (usize i = 1; i <= n; i++) {
    for (usize j = 1; j < i; j++) {
      if (xs[j] < xs[i]) {  // 保证是递增序列
        dp[0][i] = max(dp[0][i], dp[0][j] + 1);
      }
    }
  }
  // 从右往中间递增序列
  for (usize i = n; i >= 1; i--) {
    for (usize j = n; j > i; j--) {
      if (xs[j] < xs[i]) {  // 保证是递减序列
        dp[1][i] = max(dp[1][i], dp[1][j] + 1);
      }
    }
  }

  int ans = n;  // 最少去除人数
  for (usize i = 1; i <= n; i++) {
    int rem = -1;  // 去除重复计算的分隔值
    rem += dp[0][i];
    rem += dp[1][i];
    ans = min(ans, n - rem);
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  glee_queue();
  return 0;
}
