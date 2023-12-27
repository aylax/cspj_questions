// --------------------------------------------------------
// File: 探索迷宫问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <queue>
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
// 定义坐标对象
struct pos {
  int x;
  int y;
};

// --------------------------------------------------------
// Fn: 探索迷宫问题
// 题解: bfs广度优先搜索
// 用队列记录四周的访问情况
void explore_maze() {
  int n, m;  //  n 行, m 列
  std::cin >> n;
  m = n;

  // 存放地图点位信息
  std::vector<std::vector<char>> cmap(n, std::vector<char>(m));

  // 存放地图各个点位的访问情况: true 已访问; false 未访问
  std::vector<std::vector<bool>> vmap(n, std::vector<bool>(m));

  // 读入地图数据
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> cmap[i][j];
    }
  }

  // 读入 a, b点的坐标
  pos a, b;
  std::cin >> a.y >> a.x;
  std::cin >> b.y >> b.x;

  // 方位数组
  std::vector<pos> d4 = {
      {x : +0, y : -1},  // North
      {x : +0, y : +1},  // South
      {x : -1, y : +0},  // West
      {x : +1, y : +0},  // East

  };

  // Lambda: 判断坐标点是否在地图上
  auto reachable = [&n, &m](pos cur) -> bool {
    return cur.y >= 0 && cur.y < n && cur.x >= 0 && cur.x < m;
  };

  // Lambda: 判断是否可通行
  auto road_present = [&cmap](pos cur) -> bool {
    return cmap[cur.y][cur.x] == '.';
  };

  // Lambda: 判断当前节点是否已经访问
  auto has_visited = [&vmap](pos cur) -> bool { return vmap[cur.y][cur.x]; };

  // Lambda: 标记当前节点已经访问
  auto mark_visit = [&vmap](pos cur) -> void { vmap[cur.y][cur.x] = true; };

  // Lambda: 判断是否到达终点
  auto reach_end = [&b](pos &cur) -> bool {
    return cur.x == b.x && cur.y == b.y;
  };

  // Lambda: bfs
  auto bfs = [&](pos start) -> bool {
    mark_visit(start);

    std::queue<pos> q;
    q.push(start);

    while (!q.empty()) {
      pos cur = q.front();
      q.pop();

      // 只要有一条路径能到达终点, 就结束搜索
      if (reach_end(cur)) {
        return true;
      }

      // 访问周围四个方位
      for (auto d : d4) {
        pos next;
        next.x = cur.x + d.x;
        next.y = cur.y + d.y;
        if (reachable(next)) {
          if (road_present(next) && !has_visited(next)) {
            mark_visit(next);
            q.push(next);
          }
        }
      }
    }
    return false;
  };

  // 从A点出发是否能到达B点
  bool ans = bfs(a);

  std::cout << (ans ? "YES" : "NO") << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";

#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/explore_maze.in", "r", stdin);
#endif

  int k;  // k组数据
  std::cin >> k;
  for (int i = 0; i < k; i++) {
    explore_maze();
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif
  return 0;
}