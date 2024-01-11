// --------------------------------------------------------
// File: 求二叉树前序01问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <string>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 0  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名
using string = std::string;
using usize = int;

// --------------------------------------------------------
// 定义对象
string dlr_seq;  // 前序遍历序列
string ldr_seq;  // 中序遍历序列
string lrd_seq;  // 后序遍历序列

// 定义范围
struct range {
  usize left;
  usize right;
};

// --------------------------------------------------------
// Fn: 递归前序遍历
void dlr_rec(range ldr, range lrd) {
  if (ldr.left > ldr.right) return;

  // 根节点为后序序列最后一个元素
  char root = lrd_seq[lrd.right];

  // 中序遍历下, 根节点索引
  usize ldr_root_idx = ldr_seq.find(root);

  // 中序遍历下, 根节点的左子树元素个数
  usize left_subtree_cnt = ldr_root_idx - ldr.left;

  // 中序遍历下, 左右子树区间
  range next_ldr_l = {ldr.left, ldr_root_idx - 1};
  range next_ldr_r = {ldr_root_idx + 1, ldr.right};

  // 后序遍历下, 左子树区间结束位置
  usize lrd_left_end = lrd.left + left_subtree_cnt;

  // 后序遍历下, 左右子树区间
  range next_lrd_l = {lrd.left, lrd_left_end - 1};
  range next_lrd_r = {lrd_left_end, lrd.right - 1};

  // 递归求解: 顺序=> 根 左 右
  dlr_seq += root;
  dlr_rec(next_ldr_l, next_lrd_l);
  dlr_rec(next_ldr_r, next_lrd_r);
}

// --------------------------------------------------------
// Fn: 求二叉树前序01问题
// 题解: 构建树形结构
void dlr_tree_01() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/dlr_tree_01.in", "r", stdin);
#endif

  // read data
  std::cin >> ldr_seq;
  std::cin >> lrd_seq;

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  // process
  usize len_ldr_seq = ldr_seq.size();
  usize len_lrd_seq = lrd_seq.size();

  range ldr = {0, len_ldr_seq - 1};
  range lrd = {0, len_ldr_seq - 1};
  // 递归求解
  dlr_rec(ldr, lrd);

  std::cout << dlr_seq << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  dlr_tree_01();
  return 0;
}