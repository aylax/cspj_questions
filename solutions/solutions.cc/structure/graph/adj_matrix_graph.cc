
// --------------------------------------------------------
// File: 邻接矩阵图问题
// Adjacency Matrix Graph
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
using n2d = std::vector<std::vector<int>>;
// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 邻接矩阵图问题
// 题解: 构建图结构
void adj_matrix_graph() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/adj_matrix_graph.in", "r", stdin);
#endif

  int n, m;  // n个点, m条边
  std::cin >> n >> m;

  // 邻接矩阵
  int a;     // 0: 有向边, 1: 无向边
  int x, y;  // 点 x, y
  n2d graph(n, std::vector<int>(n, 0));
  for (int i = 0; i < m; i++) {
    std::cin >> a >> x >> y;
    graph[x][y] = 1;
    if (a == 1) {
      graph[y][x] = 1;
    }
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  // 输出
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << graph[i][j] << " ";
    }
    std::cout << "\n";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  adj_matrix_graph();
  return 0;
}