// --------------------------------------------------------
// File: 自然数全排列问题
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
// Fn: 自然数全排列问题
// 题解: dfs深度优先搜索
void numeric_pattern() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/numeric_pattern.in", "r", stdin);
#endif

  int n;  // 自然数 n
  std::cin >> n;

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  std::vector<int> data(n + 1);
  std::vector<bool> viewed(n + 1);
  int ans = 0;  // 符合条件的数量

  // Lambda: 输出结果
  auto output = [&n, &data](int depth) {
    for (int i = 1; i < n; i++) {
      std::cout << data[i] << " ";
    }
    std::cout << data[n] << "\n";
  };

  // Lambda: dfs
  auto dfs = Y([&](auto dfs, int depth) -> void {
    // 如果深度搜索到终点, 输出
    if (depth > n) {
      output(depth);
      ans += 1;
    } else {
      // 对所有可能情况进行深搜
      for (int i = 1; i <= n; i++) {
        // 忽略已经被访问的元素
        if (!viewed[i]) {
          // 标记访问节点, 并继续深搜
          viewed[i] = true;
          data[depth] = i;
          dfs(depth + 1);

          // 深搜结束, 取消访问标记
          viewed[i] = false;
        }
      }
    }
  });

  // Execute
  dfs(1);
  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  numeric_pattern();
  return 0;
}