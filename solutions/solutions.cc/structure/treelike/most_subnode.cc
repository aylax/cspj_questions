// --------------------------------------------------------
// File: 寻找具有最多子节点的节点问题
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

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 寻找具有最多子节点的节点问题
// 题解: 构建树形结构
void most_subnode() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/most_subnode.in", "r", stdin);
#endif

  int node_cnt, edge_cnt;  // 节点数, 边数
  std::cin >> node_cnt >> edge_cnt;

  // 录入树节点信息
  int len = 1002, child, parent;
  std::vector<int> nodes(len, -1);
  std::vector<int> count(len, 0);
  for (int i = 0; i < edge_cnt; i++) {
    std::cin >> parent >> child;
    nodes[child] = parent;
    count[parent] += 1;

    // 如果父节点还未录入, 则将值初始化为0
    if (nodes[parent] == -1) {
      nodes[parent] = 0;
    }
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  int root = 0;
  while (nodes[root] != 0) root += 1;  // 寻找根节点
  std::cout << root << "\n";

  // 寻找<具有最多子节点>的节点
  int subnode = 0;
  for (int i = 0; i < len; i++) {
    if (count[i] > count[subnode]) {
      subnode = i;
    }
  }
  std::cout << subnode << "\n";

  // 输出 subnode 的所有孩子节点
  for (int i = 0; i < len; i++) {
    if (nodes[i] == subnode) {
      std::cout << i << " ";
    }
  }
  std::cout << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  most_subnode();
  return 0;
}