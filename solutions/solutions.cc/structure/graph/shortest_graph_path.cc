
// --------------------------------------------------------
// File: 最短路线图问题
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

#define inf 0x7fffffff  // 正无穷大

struct edge;
// --------------------------------------------------------
// 设定类型别名
using n2d = std::vector<std::vector<int>>;
using n2e = std::vector<std::vector<edge>>;
// --------------------------------------------------------
// 定义对象
struct edge {
  int u, v, w;  // 点u, 点 v, 权值w
  edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

struct node {
  int id;    // 路径点u
  int dist;  // 源点s到u的最短距离 (inf表示不可达)

  // 实现优先队列比较运算
  friend bool operator<(const node &a, const node &b) {
    return a.dist > b.dist;
  }
};

// --------------------------------------------------------
// Fn: 判断整数是否是无穷大
bool is_abs_inf(int a) { return a == inf || a == -inf; }

// --------------------------------------------------------
// Fn: 整数加法越界处理
int safe_add(int a, int b) {
  if (a > 0 && b > inf - a) return inf;
  if (a < 0 && b < -inf - a) return -inf;
  return a + b;
}

// --------------------------------------------------------
// Fn: 对输入数据进行距离转换
// (u, v, w) 转换成 dist[u][v] = w 形式的邻接矩阵
void graph_into_dist(n2d &dist, n2e &graph, int n) {
  // dist(s, s) = 0
  for (int s = 0; s <= n; s++) dist[s][s] = 0;
  // dist(u, v) = w
  for (int u = 1; u <= n; u++) {
    for (auto &[_, v, w] : graph[u]) {
      dist[u][v] = w;
    }
  }
}

// --------------------------------------------------------
// Fn: 输出图中源点S到N个点的最短距离
void output(std::vector<int> &dist, int n, int s) {
  for (int u = 1; u <= n; u++) {
    std::cout << "dist[" << s;
    std::cout << "->" << u << "]=";
    if (is_abs_inf(dist[u])) {
      std::cout << "INF; ";
    } else {
      std::cout << dist[u] << "; ";
    }
  }
  std::cout << "\n";
}

// --------------------------------------------------------
// Fn: Floyd算法
// 每一个点到其余各点的最短路线 (允许图中存在负边权)
// 时间复杂度: O(n^3), 空间复杂度: O(n^2)
void floyd(n2e &graph, int n, int s) {
  n2d dist(n + 1, std::vector<int>(n + 1, inf));
  graph_into_dist(dist, graph, n);

  // 枚举路线(U, V)的<中间路径K>
  // 如果通过经过<路径点K>[U->K->V], 使得 dist(U, V)路线长度变短
  // 就修正dist(U,V)的最短路线值
  for (int k = 1; k <= n; k++) {
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v <= n; v++) {
        int w = safe_add(dist[u][k], dist[k][v]);
        dist[u][v] = std::min(dist[u][v], w);
      }
    }
  }

  // 源点 s -> 终点n的最短距离
  std::cout << dist[s][n] << "\n";

  // 输出源点s到各个点的最短距离
  // output(dist[s], n, s);
}

// --------------------------------------------------------
// Fn: Bellman Ford算法
// 求源点s到其余各点的最短路线 (允许图中存在负边权)
// 时间复杂度: O(Node * Edge), 空间复杂度: O(n^2)
void bellman_ford(n2e &graph, int n, int s) {
  std::queue<int> q;                  // 队列存入待访问的路径点
  std::vector<int> dist(n + 1, inf);  // 源点S到其余各点的最短距离
  std::vector<int> count(n + 1, 0);   // 记录最短路径经过的边数
  std::vector<bool> visited(n + 1, false);  // 记录路径点访问情况

  // 源点 s->s 距离为0
  dist[s] = 0;
  q.push(s), visited[s] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop(), visited[u] = false;

    // 枚举所有<路径点V>, 更新最短路径值
    // 如果通过经过<路径点U>[S->U->V], 使得 DP(S, V) 路线长度变短
    // 就修正DP(S,V)的最短路线值
    for (auto &[_, v, w] : graph[u]) {
      int dist_suv = safe_add(dist[u], w);
      if (dist[v] > dist_suv) {
        // 更新V的最短路线, 记录V经过的边数
        dist[v] = dist_suv;
        count[v] = count[u] + 1;

        // 最多只能访问 n-1条边, >=n则表示出现负环
        if (count[v] >= n) {
          std::cout << inf << "\n";
          return;
        }

        // 队列中加入路径点V
        if (!visited[v]) {
          q.push(v), visited[v] = true;
        }
      }
    }
  }

  // 源点 s -> 终点n的最短距离
  std::cout << dist[n] << "\n";

  // 输出源点s到各个点的最短距离
  // output(dist, n, s);
}

// --------------------------------------------------------
// Fn: Dijkstra 算法
// 求源点s到其余各点的最短路线 (无法处理负边权)
// 时间复杂度: O(n^2), 空间复杂度: O(n^2)
void dijkstra(n2e &graph, int n, int s) {
  std::priority_queue<node> q;        // 队列存入待访问的路径点
  std::vector<int> dist(n + 1, inf);  // 源点S到其余各点的最短距离
  std::vector<bool> visited(n + 1, false);  // 记录路径点访问情况

  // 源点 s->s 距离为0
  int u;
  dist[s] = 0, q.push({s, 0});
  while (!q.empty()) {
    // 取出队列中距离最短的路径点u
    u = q.top().id, q.pop();
    if (!visited[u]) {
      visited[u] = true;
      for (auto &[_, v, w] : graph[u]) {
        int dist_suv = safe_add(dist[u], w);
        if (dist[v] > dist_suv) {
          // 更新路径点v的距离后, 需要重新加入队列
          dist[v] = dist_suv;
          q.push({v, dist[v]});
        }
      }
    }
  }

  // 源点 s -> 终点n的最短距离
  std::cout << dist[n] << "\n";

  // 输出源点s到各个点的最短距离
  // output(dist, n, s);
}

// --------------------------------------------------------
// Fn: 最短路线图问题
// 题解: 构建图结构
void shortest_graph_path() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin #19
  freopen("../testdata/structure/shortest_graph_path.in", "r", stdin);
#endif

  int n, m;  // n个点, m 条边
  std::cin >> n >> m;

  int u, v, w;
  n2e graph(n + 1);
  // 存储  edge(u, v) 的权重 weight
  for (int i = 0; i < m; i++) {
    std::cin >> u >> v >> w;
    graph[u].push_back({u, v, w});
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  int s = 1;  // 源点 s

  
  // floyd(graph, n, s);
  bellman_ford(graph, n, s);
  // dijkstra(graph, n, s);
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  shortest_graph_path();
  return 0;
}