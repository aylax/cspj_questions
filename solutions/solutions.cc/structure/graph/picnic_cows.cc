
// --------------------------------------------------------
// File: 奶牛聚餐问题 (邻接矩阵)
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
using svi = std::vector<int>;
using svb = std::vector<bool>;
using n2d = std::vector<svi>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 广度遍历图 (邻接矩阵)
void bfs(n2d& graph, int u, svb& visited, svi& counter) {
  // 初始化
  std::queue<int> q;
  int n = graph.size();

  // Lambda: 访问元素
  auto visit = [&](int u) {
    q.push(u);
    counter[u] += 1;
    visited[u] = true;
  };

  visit(u);
  while (!q.empty()) {
    u = q.front();
    q.pop();
    for (int v = 1; v <= n; v++) {
      // 路径连通, 且未访问
      if (graph[u][v] == 1 && !visited[v]) {
        visit(v);
      }
    }
  }
}

// --------------------------------------------------------
// Fn: 奶牛聚餐问题 (邻接矩阵)
// 题解: 构建图结构
void picnic_cows() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/picnic_cows.in", "r", stdin);
#endif

  int k;  // k只奶牛

  std::cin >> k;

  int n, m;  // n个点, m条边
  std::cin >> n >> m;

  svi nodes(k, 0);  // 点集
  for (int i = 0; i < k; i++) {
    std::cin >> nodes[i];
  }

  int u, v;                         // 点 x, y
  n2d graph(n + 1, svi(n + 1, 0));  // 邻接矩阵

  for (int i = 0; i < m; i++) {
    std::cin >> u >> v;
    graph[u][v] = 1;
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  svb visited(n + 1);  // 元素访问情况
  svi counter(n + 1);  // 元素访问次数
  auto batch_update_view = [&visited](bool state) {
    std::fill(visited.begin(), visited.end(), state);
  };
  for (int i = 0; i < k; i++) {
    batch_update_view(false);
    bfs(graph, nodes[i], visited, counter);
  }

  int ans = 0;  // 结果
  for (int i = 1; i <= n; i++) {
    if (counter[i] == k) {
      ans += 1;
    }
  }

  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const* argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  picnic_cows();
  return 0;
}