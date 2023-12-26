// --------------------------------------------------------
// File: 农夫捉牛问题
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
struct node {
  int pos;  // 当前位置
  int cnt;  // 移动到当前位置,需要的次数
};

// --------------------------------------------------------
// cmap: 农夫捉牛问题
// 题解: bfs广度优先搜索
// 用队列记录四周的访问情况
void catch_cow() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/catch_cow.in", "r", stdin);
#endif

  int a, b;
  std::cin >> a >> b;

  int limit = 100'000;

  // 存放各个点位的信息
  std::vector<node> cmap;
  // 存放各个点位的访问情况: true 已访问; false 未访问
  std::vector<bool> vmap(limit);

  std::vector<char> methods = {'+', '-', '*'};

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  // Lambda: 判断当前位置是否可到达
  auto reachable = [&limit](int pos) -> bool {
    return pos >= 0 && pos <= limit;
  };

  // Lambda: 判断当前节点是否已经访问
  auto has_visited = [&vmap](int pos) -> bool { return vmap[pos]; };

  // Lambda: 标记当前节点已经访问
  auto mark_visit = [&vmap](int pos) -> void { vmap[pos] = true; };

  // Lambda: 判断是否到达终点
  auto reach_end = [&b](int pos) -> bool { return pos == b; };

  // Lambda: 选择指定方式后, 得出的新位置
  auto apply = [](int pos, char method) -> int {
    if (method == '+') {
      return pos + 1;
    }
    if (method == '-') {
      return pos - 1;
    }
    if (method == '*') {
      return pos * 2;
    }
    return pos;
  };

  // Lambda: bfs
  auto bfs = [&](int pos) -> int {
    mark_visit(pos);

    std::queue<node> q;
    q.push({pos : pos, cnt : 0});

    while (!q.empty()) {
      node cur = q.front();
      q.pop();
      
      // 只要有一条路径先到达终点, 就结束搜索
      if (reach_end(cur.pos)) {
        return cur.cnt;
      }

      for (char method : methods) {
        int npos = apply(cur.pos, method);
        if (reachable(npos)) {
          if (!has_visited(npos)) {
            mark_visit(npos);
            q.push({pos : npos, cur.cnt + 1});
          }
        }
      }
    }
    return -1;
  };

  int ans = -1;  // 从A点到达B点的最少移动次数

  if (reachable(a) && reachable(b)) {
    ans = bfs(a);
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// cmap: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  catch_cow();
  return 0;
}