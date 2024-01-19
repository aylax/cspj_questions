
// --------------------------------------------------------
// File: 欧拉路径问题(Euler Path)
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <stack>
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
struct degree {
  int in;   // 入度
  int out;  // 出度
};

struct info {
  int s;          // 起点
  bool is_euler;  // 是否有欧拉路径
};

// --------------------------------------------------------
// Fn : 深度遍历图(邻接表)
void dfs(n2d& graph, std::stack<int>& path, int u) {
  // 点位的访问标记
  int n = graph.size();

  // 记录访问到了 graph[u]的第几条边
  std::vector<int> link(n + 1, 0);

  // Lambda: 深度遍历, 不走重复路径
  auto _dfs = [&](auto _dfs, int u) -> void {
    int len = graph[u].size();
    // 访问 graph[u]的第i条边
    for (int i = link[u]; i < len; i = link[u]) {
      link[u] = i + 1;
      _dfs(_dfs, graph[u][i]);
    }
    path.push(u);
  };
  // 开始遍历
  _dfs(_dfs, u);
}

// --------------------------------------------------------
// Fn : 遍历输出路径
void output(std::stack<int>& path) {
  while (!path.empty()) {
    std::cout << path.top() << " ";  // 输出路径顺序
    path.pop();
  }
}

// --------------------------------------------------------
// Fn : 判断是否是欧拉图
// 定理1：存在欧拉路径的条件：图是联通的；图有且只有两个奇点。
// 定理2：存在欧拉回路的条件：图是联通的，并且没有奇点。
info is_euler_graph(std::vector<degree>& degs) {
  info ret = {s : 1, is_euler : false};
  bool euler_loop = true;
  int start_cnt = 0;  // 起点计数器，用于判断是否只有一个起点
  int end_cnt = 0;    // 终点计数器，用于判断是否只有一个终点
  for (int u = 1; u < degs.size(); u++) {
    // 奇点个数 > 1, 不是欧拉图, 返回
    if (std::abs(degs[u].in - degs[u].out) > 1) {
      return {1, false};
    }
    // 入边 != 出边, 不是欧拉回路
    if (degs[u].in != degs[u].out) {
      euler_loop = false;
    }
    // 非欧拉回路，只有一个起点
    if (degs[u].out - degs[u].in == 1) {
      ret.s = u;  // 设置起点
      start_cnt += 1;
    }

    // 非欧拉回路，只有一个终点
    if (degs[u].in - degs[u].out == 1) {
      end_cnt += 1;
    }
  }

  // 是欧拉回路, 或者 起点数量和终点数量等于1
  bool is_right_cnt = (start_cnt == 1 && end_cnt == 1);
  if (euler_loop || is_right_cnt) {
    ret.is_euler = true;
  }

  return ret;
}

// --------------------------------------------------------
// Fn: 欧拉路径问题(Euler Path)
// 题解: 构建图结构
// 寻找通过图中所有边的路径 (每条边只允许通过一次)
void euler_path() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/euler_path.in", "r", stdin);
#endif

  int n, m;  // n个点, m条边
  std::cin >> n >> m;

  int u, v;                         // 点 u, v
  n2d graph(n + 1);                 // 邻接表
  std::vector<degree> degs(n + 1);  // 每个点的度数

  for (int i = 0; i < m; i++) {
    std::cin >> u >> v;
    degs[v].in++;
    degs[u].out++;
    graph[u].push_back(v);
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

  // 判断是否是欧拉回路
  info ret = is_euler_graph(degs);

  if (ret.is_euler) {
    // 记录欧拉路径顺序
    std::stack<int> path;
    dfs(graph, path, ret.s);
    output(path);
  } else {
    std::cout << "No\n";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const* argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  euler_path();
  return 0;
}