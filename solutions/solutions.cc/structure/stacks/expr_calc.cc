// --------------------------------------------------------
// File: 后缀表达式计算问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <stack>
#include <string>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 0  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名
using std::string;
using usize = int;
using value = long long;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 后缀表达式计算问题
// 题解: 就近匹配思路
void expr_calc() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/expr_calc.in", "r", stdin);
#endif

  string expr;
  std::getline(std::cin, expr);

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  std::stack<value> ns;
  const char terminator = '@';  // 终止符
  const char splitor = '.';     // 分隔符

  // Lambda: 算术运算
  auto add = [](value a, value b) { return a + b; };
  auto sub = [](value a, value b) { return a - b; };
  auto mul = [](value a, value b) { return a * b; };
  auto div = [](value a, value b) { return a / b; };

  // Lambda: 算术运算选择器
  auto calcby = [&](char op, value a, value b) {
    if (op == '+') return add(a, b);
    if (op == '-') return sub(a, b);
    if (op == '*') return mul(a, b);
    if (op == '/') return div(a, b);
    return 0LL;
  };

  // Lambda: 判断是否是数字字符
  auto isdegit = [](char ch) { return ch >= '0' && ch <= '9'; };

  // Lambda: 判断是否是支持的运算形式
  auto isoperator = [](char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
  };

  // 初始化索引 i, 表达式长度 len
  usize i = 0, len = expr.size();

  // 从左往右读到终止符就结束
  while (i < len && expr[i] != terminator) {
    // 跳过分隔符
    while (i < len && expr[i] == splitor) i += 1;

    // 如果跳过分隔符后, 已经是字符串末尾, 跳出
    if (i >= len) break;

    // 截取数字字符片段
    if (isdegit(expr[i])) {
      value num = 0;
      // 数字字符片段转换成数字
      while (i < len && expr[i] != splitor) {
        num = num * 10 + (expr[i] - '0');
        i += 1;
      }
      ns.push(num);
    } else if (isoperator(expr[i])) {  // 读到操作符, 则计算数值
      char op = expr[i];
      value a = ns.top();
      ns.pop();
      value b = ns.top();
      ns.pop();
      value c = calcby(op, b, a);
      ns.push(c);
      i += 1;
    }
  }

  std::cout << ns.top() << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  expr_calc();
  return 0;
}