// --------------------------------------------------------
// File: 求二叉树前序02问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <string>
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
  usize idxl;
  usize idxr;
};

// --------------------------------------------------------
// Fn: 字符转索引
usize alpha_to_idx(char ch) { return ch == '*' ? 0 : ch - 'a' + 1; }

// --------------------------------------------------------
// Fn: 索引转字符
char idx_to_alpha(usize idx) { return idx == 0 ? '*' : 'a' + idx - 1; }

// --------------------------------------------------------
// Fn: 读取行数据
void read_line(const std::string &line, array &nodes) {
  usize root = alpha_to_idx(line[0]);
  usize idxl = alpha_to_idx(line[1]);
  usize idxr = alpha_to_idx(line[2]);
  nodes[root] = {idxl, idxr};
}

// --------------------------------------------------------
// Fn: 前序遍历
void dlr_tree(usize root, array &nodes) {
  if (root == 0) return;
  // 递归求解: 顺序=> 根 左 右
  std::cout << idx_to_alpha(root);
  dlr_tree(nodes[root].idxl, nodes);
  dlr_tree(nodes[root].idxr, nodes);
}

// --------------------------------------------------------
// Fn: 求二叉树前序02问题
// 题解: 构建树形结构
void dlr_tree_02() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/dlr_tree_02.in", "r", stdin);
#endif

  usize n;  // n 个节点
  std::cin >> n;

  std::string line;
  array nodes(27);

  // 读取第一行数据
  std::cin >> line;
  read_line(line, nodes);
  usize root = alpha_to_idx(line[0]);

  for (usize i = 1; i < n; i++) {
    std::cin >> line;
    read_line(line, nodes);
  }

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  dlr_tree(root, nodes);
  std::cout << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  dlr_tree_02();
  return 0;
}