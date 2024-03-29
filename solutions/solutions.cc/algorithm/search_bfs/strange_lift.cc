// --------------------------------------------------------
// File: 电梯移动问题
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
// 定义结点对象
struct node {
  int pos;     // 楼层位置
  int cnt;     // 移动到当前楼层,需要按下的按键次数
  int offset;  // 位移层数
};

// --------------------------------------------------------
// Fn: 电梯移动问题
// 题解: bfs广度优先搜索
// 用队列记录四周的访问情况
void strange_lift() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/algorithm/strange_lift.in", "r", stdin);
#endif

  int n;
  std::cin >> n;

  // 读入 a, b楼层
  int a, b;
  std::cin >> a >> b;

  // 存放各个点位的信息
  std::vector<node> cmap(n + 1);

  // 存放各个点位的访问情况: true 已访问; false 未访问
  std::vector<bool> vmap(n + 1);

  std::vector<char> methods = {'+', '-'};

  // 读入数据
  for (int i = 1; i <= n; i++) {
    cmap[i].pos = i;
    std::cin >> cmap[i].offset;
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  // Lambda: 判断当前位置是否可到达
  auto reachable = [&n](int pos) -> bool { return pos > 0 && pos <= n; };

  // Lambda: 判断当前节点是否已经访问
  auto has_visited = [&vmap](int pos) -> bool { return vmap[pos]; };

  // Lambda: 标记当前节点已经访问
  auto mark_visit = [&vmap](int pos) -> void { vmap[pos] = true; };

  // Lambda: 判断是否到达终点
  auto reach_end = [&b](int pos) -> bool { return pos == b; };

  // Lambda: 选择指定方式后, 得出的新位置
  auto apply = [](node cur, char method) -> int {
    if (method == '+') {
      return cur.pos + cur.offset;
    }
    if (method == '-') {
      return cur.pos - cur.offset;
    }
    return cur.pos;
  };

  // Lambda: bfs
  auto bfs = [&](node start) -> int {
    mark_visit(start.pos);

    std::queue<node> q;
    q.push(start);

    while (!q.empty()) {
      node cur = q.front();
      q.pop();

      // 只要有一条路径先到达终点, 就结束搜索
      if (reach_end(cur.pos)) {
        return cur.cnt;
      }

      for (char method : methods) {
        int npos = apply(cur, method);
        if (reachable(npos)) {
          if (!has_visited(npos)) {
            node next = cmap[npos];
            next.cnt = cur.cnt + 1;
            mark_visit(npos);
            q.push(next);
          }
        }
      }
    }
    return -1;
  };

  int ans = -1;  // 从A点到达B点的最少按键次数

  if (reachable(a) && reachable(b)) {
    node start = cmap[a];
    ans = bfs(start);
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  strange_lift();
  return 0;
}