// --------------------------------------------------------
// File: 数字对问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <climits>
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
// Template: Y Combinator Y运算子
// 用于实现: 在<C++>中递归调用匿名函数
// Example:
//
// auto fib = Y([](auto self, int n) {
//   if (n < 2) return 1;
//   return self(n - 1) + self(n - 2);
// });
//
// fib(5)
//
template <typename Lambda>
struct YCombinator {
  Lambda fn;

  template <typename... Args>
  decltype(auto) operator()(Args &&...args) {  // Passing *this
    return fn(*this, std::forward<Args>(args)...);
  }
};

template <typename Lambda>
decltype(auto) Y(Lambda fn) {  // Wrapper Lambda
  return YCombinator<Lambda>{fn};
}

// --------------------------------------------------------
// Fn: GCD 最大公约数
int gcd(int a, int b) {
  int t;
  while (b != 0) {
    t = a % b;
    a = b;
    b = t;
  }
  return a;
}

// --------------------------------------------------------
// Fn: 数字对问题
// 题解: dfs深度优先搜索
// 参照<辗转相除法>求解最大公约数的过程
// GCD(a, b) == GCD(b, a%b),
// 这一个操作然后消耗步长: Step = a / b
void numeric_pair() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/numeric_pair.in", "r", stdin);
#endif

  int n;  // 自然数 n
  std::cin >> n;

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  int ans = INT_MAX;  // 符合条件的数量

  // Lambda: dfs
  // required: a > b
  auto dfs = Y([&ans](auto dfs, int a, int b, int step) -> void {
    if (b == 1) {
      ans = std::min(ans, step + a - 1);
    } else {
      dfs(b, a % b, step + a / b);
    }
  });

  for (int i = 1; i <= n; i++) {
    if (gcd(n, i) == 1) {
      dfs(n, i, 0);
    }
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  numeric_pair();
  return 0;
}