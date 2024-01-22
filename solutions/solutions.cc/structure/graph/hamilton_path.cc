
// --------------------------------------------------------
// File: 哈密顿路径问题(Hamilton Path)
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

#define inf 0x7fffffff  // 正无穷大

// --------------------------------------------------------
// 设定类型别名
using n2d = std::vector<std::vector<int>>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 整数加法越界处理
int safe_add(int a, int b) {
  if (a > 0 && b > inf - a) return inf;
  if (a < 0 && b < -inf - a) return -inf;
  return a + b;
}

// --------------------------------------------------------
// Fn: 路线以二进制格式下第k位是否是1
// 此处表示: 第k种路线是否经过第u个点
bool reachable(int k, int u) { return (k >> u) & 1; }

// --------------------------------------------------------
// Fn: 输出哈密顿路径最短路径
void output_path(n2d &dp, int n) {
  int ks = 1 << n;
  int ans = dp[ks - 1][n - 1];
  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: 输出哈密顿回路最短路径
void output_loop(n2d &dp, n2d &w, int n) {
  int ks = 1 << n;
  int ans = inf;
  for (int u = 1; u < n; u++) {
    if (w[u][0] > 0) {  // 终点U与出生点0连通
      int tmp = safe_add(dp[ks - 1][u], w[u][0]);
      ans = std::min(ans, tmp);
    }
  }
  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: 哈密顿路径问题(Hamilton Path)
// 题解: 构建图结构
// 定义:
// 哈密顿路径:  (每个点只通过一次)
// => 通过图中所有点的路径
// 哈密顿回路: (除起点外, 每个点只通过一次)
// => 从起点出发, 通过图中所有点, 最终回到起点
void hamilton_path() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/hamilton_path.in", "r", stdin);
#endif

  int n;  // n个点
  std::cin >> n;

  // 存储  edge(u, v) 的权重 weight
  n2d w(n, std::vector<int>(n, 0));

  // 录入权重信息
  for (int u = 0; u < n; u++) {
    for (int v = 0; v < n; v++) {
      std::cin >> w[u][v];
    }
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  // n个路径点, 每个都存在 (经过|未经过) 两种状态
  // 所以存在 2 ^ n 种不同的路线
  int ks = 1 << n;

  // 二维数组: dp[路线][终点] = 最短路径的权重累计值
  // 路线情况: bit位存储对应点的途径状态, 1: 经过, 0: 未经过
  n2d dp(ks, std::vector<int>(n, inf));

  // Lambda: <路线K, 终点U>, 途径<路径点V>时的累计权重
  auto fn = [&](int k, int v, int u) -> int {
    // [k ^ (1 << u)]: 表示<路线K>排除<路径点U>
    return safe_add(dp[k ^ (1 << u)][v], w[v][u]);
  };

  dp[0][0] = 0;  // 初始点累计权重为0
  // 测试每一条路线
  for (int k = 1; k < ks; k++) {
    // 遍历每一个路径点
    for (int u = 0; u < n; u++) {
      // 如果 <路线K> 经过 <路径点U>
      if (reachable(k, u)) {
        for (int v = 0; v < n; v++) {
          // 如果 <路线K> 经过 <路径点V>
          if (reachable(k, v)) {
            // 计算<路线K, 终点U>的最少累计权重
            dp[k][u] = std::min(dp[k][u], fn(k, v, u));
          }
        }
      }
    }
  }

  // 哈密顿路径最短路径
  output_path(dp, n);
  // 哈密顿回路最短路径
  output_loop(dp, w, n);
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  hamilton_path();
  return 0;
}