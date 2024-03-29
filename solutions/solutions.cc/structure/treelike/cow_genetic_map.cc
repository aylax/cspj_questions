// --------------------------------------------------------
// File: 奶牛遗传图谱问题
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
using str = std::string;
using usize = int;

// --------------------------------------------------------
// 定义对象
str dlr_seq;  // 前序遍历序列
str ldr_seq;  // 中序遍历序列
str lrd_seq;  // 后序遍历序列

// 定义范围
struct range {
  usize left;
  usize right;
};

// --------------------------------------------------------
// Fn: 递归前序遍历
void lrd_rec(range dlr, range ldr) {
  if (ldr.left > ldr.right) return;

  // 根节点为前序序列第一个元素
  char root = dlr_seq[dlr.left];

  // 中序遍历下, 根节点索引
  usize ldr_root_idx = ldr_seq.find(root);

  // 中序遍历下, 根节点的左子树元素个数
  usize left_subtree_cnt = ldr_root_idx - ldr.left;

  // 中序遍历下, 左右子树区间
  range next_ldr_l = {ldr.left, ldr_root_idx - 1};
  range next_ldr_r = {ldr_root_idx + 1, ldr.right};

  // 前序遍历下, 左子树区间结束位置
  usize dlr_left_end = dlr.left + left_subtree_cnt;

  // 前序遍历下, 左右子树区间
  range next_dlr_l = {dlr.left + 1, dlr_left_end};
  range next_dlr_r = {dlr_left_end + 1, dlr.right};

  // 递归求解: 顺序=> 左 右 根
  lrd_rec(next_dlr_l, next_ldr_l);
  lrd_rec(next_dlr_r, next_ldr_r);
  lrd_seq += root;
}

// --------------------------------------------------------
// Fn: 奶牛遗传图谱问题
// 题解: 构建树形结构
void cow_genetic_map() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/cow_genetic_map.in", "r", stdin);
#endif

  // read data
  std::cin >> ldr_seq;
  std::cin >> dlr_seq;

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  // process
  usize len_dlr_seq = dlr_seq.size();
  usize len_ldr_seq = ldr_seq.size();

  range dlr = {0, len_dlr_seq - 1};
  range ldr = {0, len_ldr_seq - 1};
  // 递归求解
  lrd_rec(dlr, ldr);

  std::cout << lrd_seq << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  cow_genetic_map();
  return 0;
}