// --------------------------------------------------------
// File: 子数组和的最大值问题
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
using value = long long;
// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: Max 获取最大值
value max(value a, value b) { return a > b ? a : b; }

// --------------------------------------------------------
// Fn: 子数组和的最大值问题
// 题解: 动态规划, 每一轮往右拓展一个元素
// 状态转移公式:
// dp[n] = xs[i] + max(0, d[n-1]);
void maxsum_subseq() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/maxsum_subseq.in", "r", stdin);
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

  std::vector<value> dp(n + 1, 0);

  dp[1] = xs[1];

  value ans = dp[1];
  for (usize i = 2; i <= n; i++) {
    dp[i] = xs[i] + max(0, dp[i - 1]);
    ans = max(ans, dp[i]);
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  maxsum_subseq();
  return 0;
}
