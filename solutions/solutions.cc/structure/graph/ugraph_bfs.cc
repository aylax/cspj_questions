
// --------------------------------------------------------
// File: 无向图的广度优先遍历问题 (邻接表)
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
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
using n2d = std::vector<std::vector<int>>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 广度遍历图 (邻接表)
void bfs(n2d& graph, int u) {
  // 初始化
  std::queue<int> q;
  int n = graph.size();
  std::vector<bool> visited(n + 1, false);

  // Lambda: 访问元素
  auto visit = [&](int u) {
    q.push(u);
    visited[u] = true;
    std::cout << u << " ";
  };

  visit(u);
  while (!q.empty()) {
    u = q.front();
    q.pop();
    for (auto v : graph[u]) {
      if (!visited[v]) {
        visit(v);
      }
    }
  }
}

// --------------------------------------------------------
// Fn: 无向图的广度优先遍历问题 (邻接表)
// 题解: 构建图结构
void ugraph_bfs() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/ugraph_bfs.in", "r", stdin);
#endif

  int n, m;  // n个点, m条边
  std::cin >> n >> m;

  int u, v;          // 点 u, v
  n2d graph(n + 1);  // 邻接表

  for (int i = 0; i < m; i++) {
    std::cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  // 升序排列
  for (int u = 1; u <= n; u++) {
    auto& ns = graph[u];
    if (ns.size() > 1) {
      std::sort(ns.begin(), ns.end());
    }
  }

  int s = 1;  // 初始点s

  // 广度优先遍历输出
  bfs(graph, s);
  std::cout << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const* argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  ugraph_bfs();
  return 0;
}