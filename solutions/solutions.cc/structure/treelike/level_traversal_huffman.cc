// --------------------------------------------------------
// File: 层序遍历哈夫曼树问题
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

struct node;
// --------------------------------------------------------
// 设定类型别名
using list = std::vector<node *>;
// --------------------------------------------------------
// 定义对象
struct elem {
  int id;
};

struct node {
  int id;
  node *lc;
  node *rc;
  node(int id) : id(id) {
    this->lc = nullptr;
    this->rc = nullptr;
  }
};

// --------------------------------------------------------
// Fn: 寻找最小节点
auto find_min(list &xs) {
  auto min_it = xs.begin();
  for (auto it = xs.begin(); it != xs.end(); it++) {
    if ((*min_it)->id > (*it)->id) {
      min_it = it;
    }
  }
  return min_it;
}
// --------------------------------------------------------
// Fn: 生成huffman树
auto huffman(list &ds, std::vector<elem> &rd) {
  // 按字典序排序
  auto inc = [](elem &a, elem &b) { return a.id < b.id; };
  std::sort(rd.begin(), rd.end(), inc);

  // 构造初始节点
  for (auto x : rd) {
    ds.push_back(new node(x.id));
  }

  // 构建哈夫曼树
  while (ds.size() > 1) {
    // 寻找较小的节点1
    auto it = find_min(ds);
    node *lc = *it;
    ds.erase(it);

    // 寻找较小的节点2
    it = find_min(ds);
    node *rc = *it;
    ds.erase(it);

    // 构建新节点
    int id = lc->id + rc->id;
    node *p = new node(id);
    p->lc = lc;
    p->rc = rc;

    // 哈夫曼树节点构造完毕, 插入堆中
    ds.push_back(p);
  }

  return ds.front();
}

// --------------------------------------------------------
// Fn: 层序遍历huffman树
void level_traversal(node *p) {
  if (p == nullptr) return;
  std::queue<node *> q;
  q.push(p);

  while (!q.empty()) {
    p = q.front();
    std::cout << p->id << " ";
    q.pop();
    if (p->lc != nullptr) {
      q.push(p->lc);
    }
    if (p->rc != nullptr) {
      q.push(p->rc);
    }
  }
}

// --------------------------------------------------------
// Fn: 层序遍历哈夫曼树问题
// 题解: 构建树形结构
void level_traversal_huffman() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/level_traversal_huffman.in", "r", stdin);
#endif

  int n;
  std ::cin >> n;

  std::vector<elem> rd(n);
  for (int i = 0; i < n; i++) {
    std::cin >> rd[i].id;
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  // 构建huffman树
  list ds;

  // 生成huffman编码
  node *root = huffman(ds, rd);
  level_traversal(root);
  std::cout << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  level_traversal_huffman();
  return 0;
}