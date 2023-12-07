// --------------------------------------------------------
// File: 乒乓计分问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>

// --------------------------------------------------------
// 预声明

// --------------------------------------------------------
// 设定类型别名
using std::string;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 乒乓计分问题
// 题解: 枚举思想
void pingpang() {
  char alpha;
  int A11 = 0, A21 = 0, B11 = 0, B21 = 0;
  std::vector<string> R11, R21;  // 11分制比赛记录, 21分制比赛记录

  // Lambda: 判断 base 分制下比赛是否结束
  auto end_of_match = [](int base, auto a, auto b) {
    return (a >= base || b >= base) && abs(a - b) >= 2;
  };

  // Lambda: 创建本局比赛结果
  auto make_record = [](auto a, auto b) {
    return std::to_string(a) + ":" + std::to_string(b);
  };

  while (std::cin >> alpha && alpha != 'E') {  // 读到 EOF 或者 字母 E结束读取
    if (alpha == 'W') {
      A11 += 1;  // 11分制: A选手本场次胜局存入
      A21 += 1;  // 21分制: A选手本场次胜局存入
    } else if (alpha == 'L') {
      B11 += 1;  // 11分制: B选手本场次胜局存入
      B21 += 1;  // 21分制: B选手本场次胜局存入
    }

    // 记录11分制下本局比赛结果
    if (end_of_match(11, A11, B11)) {
      R11.push_back(make_record(A11, B11));
      A11 = 0, B11 = 0;  // 清除本局比赛数据
    }

    // 记录21分制下本局比赛结果
    if (end_of_match(21, A21, B21)) {
      R21.push_back(make_record(A21, B21));
      A21 = 0, B21 = 0;  // 清除本局比赛数据
    }
  }

  // E强制终止时, 比赛可能未结束, 记录最后一局比赛结果
  R11.push_back(make_record(A11, B11));
  A11 = 0, B11 = 0;  // 清除本局比赛数据
  R21.push_back(make_record(A21, B21));
  A21 = 0, B21 = 0;  // 清除本局比赛数据

  // 输出 R11
  for (auto const &record : R11) {
    std::cout << record << "\n";
  }
  // 空一行
  std::cout << "\n";
  // 输出 R21
  for (auto const &record : R21) {
    std::cout << record << "\n";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  /* code */
  pingpang();
  return 0;
}
