// --------------------------------------------------------
// File: 自然数分解问题
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
// Fn: 自然数分解问题
// 题解: dfs深度优先搜索
void numeric_split() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/numeric_split.in", "r", stdin);
#endif

  int n;  // 自然数 n
  std::cin >> n;

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  std::vector<int> data;
  int ans = 0;  // 符合条件的数量

  // Lambda: 输出结果
  auto output = [&n](std::vector<int> &data) {
    int len = data.size();

    std::cout << n << "=" << data[0];
    for (int i = 1; i < len; i++) {
      std::cout << "+" << data[i];
    }
    std::cout << "\n";
  };

  // Lambda: dfs
  auto dfs = Y([&](auto dfs, int acc, int cur) -> void {
    if (cur == n || acc > n) {
      return;
    } else if (acc == n) {
      output(data);
      ans += 1;
    } else {
      //  当前拆分元素要大于等于上一个元素
      for (int i = cur; i <= (n - acc); i++) {
        data.push_back(i);
        dfs(acc + i, i);
        data.pop_back();
      }
    }
  });

  // Execute
  dfs(0, 1);
  // std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  numeric_split();
  return 0;
}