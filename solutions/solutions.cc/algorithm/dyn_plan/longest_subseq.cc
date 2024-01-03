// --------------------------------------------------------
// File: 最长上升子序列问题
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

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: Max 获取最大值
int max(int a, int b) { return a > b ? a : b; }

// --------------------------------------------------------
// Fn: 最长上升子序列问题
// 题解: 动态规划
// 状态转移公式:
// FOR k in 1..n-1:
// Let dp[n] = max(dp[n], dp[k] + 1)
void longest_subseq() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/longest_subseq.in", "r", stdin);
#endif

  int n;  // n行
  std::cin >> n;

  std::vector<int> xs(n + 1);
  std::vector<int> dp(n + 1, 1);

  for (int i = 1; i <= n; i++) {
    std::cin >> xs[i];
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (xs[j] < xs[i]) {  // 保证是递增序列
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = max(dp[i], ans);
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  longest_subseq();
  return 0;
}
