// --------------------------------------------------------
// File: 拯救公主问题
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
using c2d = std::vector<std::vector<char>>;
using v2d = std::vector<std::vector<bool>>;

// --------------------------------------------------------
struct maze {
  int row;
  int col;
  c2d map;
};

// 定义对象
struct pos {
  int x;
  int y;
};

struct node {
  pos cur;   // 当前位置坐标
  int cost;  // 移到当前位置花费的代价

  // 实现优先队列比较运算
  friend bool operator<(const node a, const node b) { return a.cost > b.cost; }
};

// --------------------------------------------------------
// Fn: 拯救公主问题
// 题解: bfs广度优先搜索
// 优先队列, 优先访问代价小的元素
void save_princess(maze data, pos first, pos last) {
  int n = data.row;  // n 行
  int m = data.col;  // m 列

  c2d &cmap = data.map;  // 地图信息

  // 存放地图各个点位的访问情况: true 已访问; false 未访问
  v2d vmap(n, std::vector<bool>(m));

  // 方位数组
  std::vector<pos> d4 = {
      pos{x : +0, y : -1},  // North
      pos{x : +0, y : +1},  // South
      pos{x : -1, y : +0},  // West
      pos{x : +1, y : +0},  // East

  };

  // Lambda: 判断坐标点是否在地图上
  auto reachable = [&n, &m](pos cur) -> bool {
    return cur.y >= 0 && cur.y < n && cur.x >= 0 && cur.x < m;
  };

  // Lambda: 判断是否可通行
  auto road_present = [&cmap](pos cur) -> bool {
    return cmap[cur.y][cur.x] != '#';
  };

  // Lambda: 判断是否有守卫阻拦
  auto guard_present = [&cmap](pos cur) -> bool {
    return cmap[cur.y][cur.x] == 'x';
  };

  // Lambda: 判断当前节点是否已经访问
  auto has_visited = [&vmap](pos cur) -> bool { return vmap[cur.y][cur.x]; };

  // Lambda: 标记当前节点已经访问
  auto mark_visit = [&vmap](pos cur) -> void { vmap[cur.y][cur.x] = true; };

  // Lambda: 判断是否到达终点
  auto reach_end = [&last](pos &cur) -> bool {
    return cur.x == last.x && cur.y == last.y;
  };

  // Lambda: bfs
  auto bfs = [&](pos start) -> int {
    mark_visit(start);

    // 优先队列, 优先访问代价小的元素
    std::priority_queue<node> q;
    q.push({cur : start, cost : 0});

    while (!q.empty()) {
      node about = q.top();
      q.pop();

      // 只要有一条路径能到达终点, 就结束搜索
      if (reach_end(about.cur)) {
        return about.cost;
      }

      // 访问周围四个方位
      for (auto d : d4) {
        pos next;
        next.x = about.cur.x + d.x;
        next.y = about.cur.y + d.y;
        if (reachable(next)) {
          if (road_present(next) && !has_visited(next)) {
            mark_visit(next);
            int cost = about.cost;
            if (guard_present(next)) {
              q.push({cur : next, cost : cost + 2});
            } else {
              q.push({cur : next, cost : cost + 1});
            }
          }
        }
      }
    }
    return -1;
  };

  // 从起点出发是否能到达终点
  int ans = bfs(first);
  if (ans > 0) {
    std::cout << ans << "\n";
  } else {
    std::cout << "Impossible\n";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";

#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/save_princess.in", "r", stdin);
#endif

  int k;  // k组数据
  std::cin >> k;
  for (int i = 0; i < k; i++) {
    int n, m;
    std::cin >> n >> m;

    // 记录骑士和公主的坐标
    pos knight, princess;

    // 记录骑士和公主的出现次数
    int kcnt = 0, pcnt = 0;
    // 存放地图点位信息
    maze data = {row : n, col : m};
    data.map.resize(n);
    // 读入地图数据
    for (int i = 0; i < n; i++) {
      data.map[i].resize(m);
      for (int j = 0; j < m; j++) {
        std::cin >> data.map[i][j];
        if (data.map[i][j] == 'r') {
          kcnt += 1;
          knight = {x : j, y : i};
        }
        if (data.map[i][j] == 'a') {
          pcnt += 1;
          princess = {x : j, y : i};
        }
      }
    }

    // 仅允许一位骑士和一位公主
    if (kcnt == 1 && pcnt == 1) {
      save_princess(data, knight, princess);
    } else {
      std::cout << "Impossible\n";
    }
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif
  return 0;
}