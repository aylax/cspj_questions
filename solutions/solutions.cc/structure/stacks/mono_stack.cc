// --------------------------------------------------------
// File: 单调栈问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <stack>
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
using stack = std::stack<usize>;
using array = std::vector<value>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 单调栈问题
// 题解: 就近匹配思路
void mono_stack() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/mono_stack.in", "r", stdin);
#endif

  usize n;  // 元素个数 n
  std::cin >> n;
  array arr(n + 1);

  for (usize i = 1; i < n + 1; i++) {
    std::cin >> arr[i];
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  stack ms;                       // 单调栈
  std::vector<usize> ans(n + 1);  // 答案
  for (usize i = 1; i < n + 1; i++) {
    // 弹出不符合条件的元素
    while (!ms.empty() && arr[ms.top()] < arr[i]) {
      ans[ms.top()] = i;
      ms.pop();
    }
    ms.push(i);
  }

  for (usize i = 1; i < n + 1; i++) {
    std::cout << ans[i] << " ";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  mono_stack();
  return 0;
}