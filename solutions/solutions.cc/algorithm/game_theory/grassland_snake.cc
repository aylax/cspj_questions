// --------------------------------------------------------
// File: 草原贪吃蛇问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <cmath>
#include <deque>
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 1  // 1: Open, 0: Close
#endif

struct snake;
// --------------------------------------------------------
// 设定类型别名

// --------------------------------------------------------
// 定义节点对象
struct snake {
  int id;  // 编号
  int hp;  // 体力值

  snake() = default;
  snake(int id, int hp) : id(id), hp(hp) {}

  bool operator<(const snake& other) const {
    auto self = *this;
    if (self.hp == other.hp) {
      return self.id < other.id;
    } else {
      return self.hp < other.hp;
    }
  }
};

// --------------------------------------------------------
// Fn: 草原贪吃蛇问题
// 题解: 对策论思想，寻找奇异局势
// 分析:
// 首先我们定义奇异局势为：选手面对奇异局势时必输。
// 所以，对于博弈游戏的分析转化为寻找奇异局势。
void grassland_snake() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/grassland_snake.in", "r", stdin);
#endif

  int n;  // n条蛇
  std::cin >> n;

  // 记录每一条蛇的体力值
  std::vector<snake> xs(n);
  for (int i = 0; i < n; ++i) {
    xs[i].id = i + 1;
    std::cin >> xs[i].hp;
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  std::deque<snake> q0;
  std::deque<snake> q1;

  for (int i = 0; i < n; ++i) {
    std::cout << xs[i].hp << " ";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const* argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  grassland_snake();
  return 0;
}