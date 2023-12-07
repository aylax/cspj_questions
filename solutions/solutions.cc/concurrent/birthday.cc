// --------------------------------------------------------
// File: 一起送上生日祝福
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// --------------------------------------------------------
// 预声明
#define _TESTDATA_ 1  // stdin redirect testdata/

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using std::string;
using array = std::vector<string>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: Happy Birthday
void happy_birthday() {
#ifdef _TESTDATA_
  // set birthday.in -> stdin
  freopen("./testdata/birthday.in", "r", stdin);
#endif
  // N blessings
  usize n;
  std::cin >> n;

  std::cin.ignore();  // 忽略第一行
  // read blessing
  array blessing(n);
  for (usize i = 0; i < n; i++) {
    std::getline(std::cin, blessing[i]);
  }

  // close stdin
#ifdef _TESTDATA_
  fclose(stdin);
#endif

  // Lambda: say blessing
  auto say = [](string s) { std::cout << s + "\n"; };

  // add tasks
  std::vector<std::thread> tasks(n);
  for (usize i = 0; i < n; i++) {
    tasks[i] = std::thread(say, blessing[i]);
  }

  // exec tasks: 主线程会在最后阻塞, 直到全部join的任务完成
  for (usize i = 0; i < n; i++) {
    tasks[i].join();
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  happy_birthday();
  return 0;
}