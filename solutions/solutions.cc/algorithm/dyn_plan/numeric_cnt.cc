// --------------------------------------------------------
// File: 数的计算问题
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
// Fn: 数的计算问题
// 题解: 动态规划
// 寻找规律
// f[0]=0
// f[1]=1=f[0]+1
// f[2]=2=f[1]+1
// f[3]=2=f[1]+1
// f[4]=4=f[1]+f[2]+1
// f[5]=4=f[1]+f[2]+1
// 得出推导公式:
// F(i) = Sum(i/2) + 1
// Sum(i) = Sum(i-1) + F(i)
void numeric_cnt() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/numeric_cnt.in", "r", stdin);
#endif

  int n;  // 自然数 n
  std::cin >> n;

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  std::vector<int> dp(n);

  int fi, ans = 0;  // fi的值, 符合条件的数量

  dp[0] = 0;
  for (int i = 1; i <= (n / 2); i++) {
    fi = dp[i / 2] + 1;
    dp[i] = dp[i - 1] + fi;
  }

  ans = dp[n / 2] + 1;
  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  numeric_cnt();
  return 0;
}