// --------------------------------------------------------
// File: 模板队列实现问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <queue>

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
using queue = std::queue<value>;

// --------------------------------------------------------
// 定义对象
enum operation {
  push = 1,
  pop,
  top,
  size,
};

// --------------------------------------------------------
// Fn: 模板队列实现问题
// 题解: 队列基本操作
void template_queue() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/template_queue.in", "r", stdin);
#endif

  usize n;
  std::cin >> n;
  queue nq;

  value op, val;
  for (usize i = 0; i < n; i++) {
    std::cin >> op;
    if (operation::push == op) {
      std::cin >> val;
      nq.push(val);
    } else if (operation::pop == op) {
      if (nq.empty()) {
        std::cout << "ERR_CANNOT_POP\n";
      } else {
        nq.pop();
      }
    } else if (operation::top == op) {
      if (nq.empty()) {
        std::cout << "ERR_CANNOT_QUERY\n";
      } else {
        std::cout << nq.front() << "\n";
      }
    } else if (operation::size == op) {
      std::cout << nq.size() << "\n";
    } else {
      std::cout << "ERR_OPERATION\n";
    }
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  template_queue();
  return 0;
}