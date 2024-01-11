// --------------------------------------------------------
// File: 求二叉树的前序、中序、后序遍历问题
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

struct node;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using array = std::vector<node>;

// --------------------------------------------------------
// 定义对象
struct node {
  usize data;
  usize idxl;
  usize idxr;
};

// --------------------------------------------------------
// Fn: 前序遍历
void dlr_tree(usize idxc, array& nodes, usize node_cnt) {
  if (idxc < 1 || idxc > node_cnt) return;
  std::cout << nodes[idxc].data << " ";
  dlr_tree(nodes[idxc].idxl, nodes, node_cnt);
  dlr_tree(nodes[idxc].idxr, nodes, node_cnt);
}

// --------------------------------------------------------
// Fn: 中序遍历
void ldr_tree(usize idxc, array& nodes, usize node_cnt) {
  if (idxc < 1 || idxc > node_cnt) return;
  ldr_tree(nodes[idxc].idxl, nodes, node_cnt);
  std::cout << nodes[idxc].data << " ";
  ldr_tree(nodes[idxc].idxr, nodes, node_cnt);
}

// --------------------------------------------------------
// Fn: 后序遍历
void lrd_tree(usize idxc, array& nodes, usize node_cnt) {
  if (idxc < 1 || idxc > node_cnt) return;
  lrd_tree(nodes[idxc].idxl, nodes, node_cnt);
  lrd_tree(nodes[idxc].idxr, nodes, node_cnt);
  std::cout << nodes[idxc].data << " ";
}

// --------------------------------------------------------
// Fn: 求二叉树的前序、中序、后序遍历问题
// 题解: 构建树形结构
// NOTE: 二叉树性质
// idxc 为父节点索引; idxl 左节点索引; idxr 右节点索引
// idxl = 2 * idxc; idxr = 2 * idxc + 1
void traversal_tree() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/traversal_tree.in", "r", stdin);
#endif

  usize node_cnt;
  std::cin >> node_cnt;

  array nodes(node_cnt + 1);
  for (usize i = 1; i <= node_cnt; i++) {
    std::cin >> nodes[i].data;

    usize idxl = i * 2;
    usize idxr = i * 2 + 1;
    if (idxl <= node_cnt) nodes[i].idxl = idxl;
    if (idxr <= node_cnt) nodes[i].idxr = idxr;
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  // 前序遍历
  dlr_tree(1, nodes, node_cnt);
  std::cout << "\n";
  // 中序遍历
  ldr_tree(1, nodes, node_cnt);
  std::cout << "\n";
  // 后序遍历
  lrd_tree(1, nodes, node_cnt);
  std::cout << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const* argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  traversal_tree();
  return 0;
}