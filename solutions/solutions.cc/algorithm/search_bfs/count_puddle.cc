// --------------------------------------------------------
// File: 水坑数量问题
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
// 定义对象
struct pos {
  int x;
  int y;
};

// --------------------------------------------------------
// Fn: 水坑数量问题
// 题解: bfs广度优先搜索
// 用队列记录四周的访问情况
void count_puddle() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/count_puddle.in", "r", stdin);
#endif

  int n, m;  //  n 行, m 列
  std::cin >> n >> m;

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

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  int ans = 0;  // 符合条件的数量

  // 方位数组
  std::vector<pos> d8 = {
      pos{x : +0, y : -1},  // North
      pos{x : +0, y : +1},  // South
      pos{x : -1, y : +0},  // West
      pos{x : +1, y : +0},  // East
      pos{x : -1, y : -1},  // North West
      pos{x : +1, y : -1},  // North East
      pos{x : -1, y : +1},  // South West
      pos{x : +1, y : +1},  // South East

  };

  // Lambda: 判断坐标点是否在地图上
  auto on_the_map = [&n, m](pos cur) -> bool {
    return cur.y >= 0 && cur.y < n && cur.x >= 0 && cur.x < m;
  };

  // Lambda: 判断是否为水坑
  auto puddle_present = [&cmap](pos cur) -> bool {
    return cmap[cur.y][cur.x] == 'W';
  };

  // Lambda: 判断当前节点是否已经访问
  auto has_visited = [&vmap](pos cur) -> bool { return vmap[cur.y][cur.x]; };

  // Lambda: 标记当前节点已经访问
  auto mark_visit = [&vmap](pos cur) -> void { vmap[cur.y][cur.x] = true; };

  // Lambda: bfs
  auto bfs = [&](pos start) -> void {
    mark_visit(start);

    std::queue<pos> q;
    q.push(start);

    while (!q.empty()) {
      pos cur = q.front();
      // 访问周围八个方位
      for (auto d : d8) {
        pos next;
        next.x = cur.x + d.x;
        next.y = cur.y + d.y;
        if (on_the_map(next)) {
          if (puddle_present(next) && !has_visited(next)) {
            mark_visit(next);
            q.push(next);
          }
        }
      }
      q.pop();
    }
  };

  //  从左上角开始搜索
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      pos start = {x : j, y : i};
      if (puddle_present(start) && !has_visited(start)) {
        bfs(start);
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
  count_puddle();
  return 0;
}