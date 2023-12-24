// --------------------------------------------------------
// File: 素数圆问题
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

// Fn: 平方根内求素数
bool is_prime(int n) {
  if (n % 2 == 0) {  // 偶数直接返回, 少开一次平方根
    return false;
  }
  for (int i = 2; i <= std::sqrt(n); i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

// --------------------------------------------------------
// Fn: 素数圆问题
// 题解: dfs深度优先搜索
void prime_circle() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/prime_circle.in", "r", stdin);
#endif

  int n;  // 自然数 n
  std::cin >> n;

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  std::vector<int> data(n + 1);
  std::vector<bool> viewed(n + 1);
  std::vector<bool> prime_table(2 * n + 1);  // 质数表
  int ans = 0;                             // 符合条件的数量

  // Lambda: 输出结果
  auto output = [&n, &data](int depth) {
    for (int i = 1; i < n; i++) {
      std::cout << data[i] << "";
    }
    std::cout << data[n] << "\n";
  };

  // Lambda: dfs
  auto dfs = Y([&](auto dfs, int depth) -> void {
    // 如果深度搜索到终点, 输出
    if (depth > n) {
      // 因为是环, 首尾也要求和判断是否是素数
      if (prime_table[data[1] + data[depth - 1]]) {
        output(depth);
        ans += 1;
      }
    } else {
      // 对所有可能情况进行深搜
      for (int i = 1; i <= n; i++) {
        // 忽略已经被访问的元素
        if (!viewed[i]) {
          // 深度为1 或者 当前满足和为素数, 才进行深度搜索
          if (depth == 1 || prime_table[i + data[depth - 1]]) {
            // 标记访问节点, 并继续深搜
            viewed[i] = true;
            data[depth] = i;
            dfs(depth + 1);

            // 深搜结束, 取消访问标记
            viewed[i] = false;
          }
        }
      }
    }
  });

  if (n == 1) {  // 一个元素
    std::cout << 1 << "\n";
    std::cout << 1 << "\n";
  } else if (n % 2 == 0) {  // 偶数才有可能有素数环
    // 素数打表
    for (int i = 1; i < 2 * n + 1; i++) {
      prime_table[i] = is_prime(i);
    }
    dfs(1);
    if (ans > 0) {
      std::cout << ans << "\n";
    } else {
      std::cout << "No Answer\n";
    }
  } else {
    std::cout << "No Answer\n";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  prime_circle();
  return 0;
}