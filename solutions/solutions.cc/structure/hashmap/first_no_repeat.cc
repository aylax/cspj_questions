// --------------------------------------------------------
// File: 第一个只出现一次的字符问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>

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
using value = int;
using array = std::vector<value>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 第一个只出现一次的字符问题
// 题解: 哈希存储
void first_no_repeat() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/first_no_repeat.in", "r", stdin);
#endif

  string data;
  std::getline(std::cin, data);

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  // 字符串长度
  usize len = data.size();

  // ASCII字符出现次数统计表
  // 0 ~ 31 & 127 功能字符, 32 ~ 126 打印字符, 128 ~ 255 扩展字符
  array count(256);

  // Lambda: 字符转数字
  auto ord = [](char ch) -> value { return ch; };

  // 记录字符串中各个字母出现次数
  for (usize i = 0; i < len; i++) {
    count[ord(data[i])] += 1;
  }

  // 找出字符串中第一个只出现一次的字符
  for (usize i = 0; i < len; i++) {
    if (count[ord(data[i])] == 1) {
      std::cout << data[i] << "\n";
      return;
    }
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  first_no_repeat();
  return 0;
}