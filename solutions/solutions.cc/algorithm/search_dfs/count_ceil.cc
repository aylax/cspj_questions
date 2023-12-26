// --------------------------------------------------------
// File: 统计细胞问题
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
struct pos {
  int x;
  int y;
};

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
// Fn: 统计细胞问题
// 题解: dfs深度优先搜索
// 遇到细胞就增加 ans
// 并将地图上该细胞四周的细胞消除
void count_ceil() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/count_ceil.in", "r", stdin);
#endif

  int n, m;  //  n 行, m 列
  std::cin >> n >> m;

  std::vector<std::vector<char>> cmap(n, std::vector<char>(m));

  // 读入地图数据
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> cmap[i][j];
    }
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  int ans = 0;  // 符合条件的数量

  // 方位数组
  std::vector<pos> d4 = {
      pos{x : +0, y : -1},  // North
      pos{x : +0, y : +1},  // South
      pos{x : -1, y : +0},  // West
      pos{x : +1, y : +0},  // East

  };

  // Lambda: 判断坐标点是否在地图上
  auto reachable = [&n, m](pos cur) -> bool {
    return cur.y >= 0 && cur.y < n && cur.x >= 0 && cur.x < m;
  };

  // Lambda: 判断是细胞坐标点
  auto ceil_present = [&cmap](pos cur) -> bool {
    return cmap[cur.y][cur.x] != '0';
  };

  // Lambda: 消除细胞
  auto remove_ceil = [&cmap](pos cur) -> void {
    cmap[cur.y][cur.x] = '0';  // 消除细胞
  };

  // Lambda: dfs
  auto dfs = Y([&](auto dfs, pos cur) -> void {
    remove_ceil(cur);  // 消除当前访问的细胞

    // 访问细胞周围四个方位
    for (auto d : d4) {
      pos next;
      next.x = cur.x + d.x;
      next.y = cur.y + d.y;
      if (reachable(next)) {
        if (ceil_present(next)) {
          dfs(next);
        }
      }
    }
  });

  //  从左上角开始搜索
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      pos cur = {x : j, y : i};
      if (ceil_present(cur)) {
        dfs(cur);
        ans += 1;
      }
    }
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  count_ceil();
  return 0;
}