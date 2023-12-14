// --------------------------------------------------------
// File: 验证栈序列问题
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
using array = std::vector<value>;
using stack = std::stack<value>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 验证栈序列问题
// 题解: 模拟出栈匹配思路
void check_pops_seq() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/check_pops_seq.in", "r", stdin);
#endif

  usize n;  // 询问次数
  std::cin >> n;

  // Lambda: 读取数据
  auto readin = [](array &arr, usize len) {
    // 读取入栈序列
    for (usize i = 0; i < len; i++) {
      std::cin >> arr[i];
    }
  };

  // Lambda: 判断出栈序列是否合法
  auto resolve = [](array &seqin, array &seqout) -> bool {
    stack s;  // 模拟入栈和出栈
    usize len = seqin.size();
    usize topout = 0;  // 指向出栈序列栈顶

    // Lambda: 符合迭代要求
    auto flag = [&s, &topout, &len]() -> bool {
      return !s.empty() && topout < len;
    };
    for (usize topin = 0; topin < len; topin++) {
      s.push(seqin[topin]);
      while (flag() && s.top() == seqout[topout]) {
        topout += 1;
        s.pop();
      }
    }

    return topout == len;
  };

  for (usize i = 0; i < n; i++) {
    usize len;
    std::cin >> len;

    // 读取入栈序列
    array seqin(len);
    readin(seqin, len);

    // 读取出栈序列
    array seqout(len);
    readin(seqout, len);

    // 解析出栈序列是否合法
    auto ans = resolve(seqin, seqout);
    std::cout << (ans ? "Yes" : "No") << "\n";
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
  check_pops_seq();
  return 0;
}