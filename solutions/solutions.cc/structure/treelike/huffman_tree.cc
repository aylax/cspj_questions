// --------------------------------------------------------
// File: 构建哈夫曼树问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <map>
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
using str = std::string;
using list = std::vector<node *>;
// --------------------------------------------------------
// 定义对象
struct elem {
  char id;
  int freq;
  str code;
};

struct node {
  char id;
  int freq;  // 频数
  node *lc;
  node *rc;
  node(char c, int f) : id(c), freq(f) {
    this->lc = nullptr;
    this->rc = nullptr;
  }
};

// --------------------------------------------------------
// Fn: 寻找最小节点
auto find_min(list &xs) {
  auto min_it = xs.begin();
  for (auto it = xs.begin(); it != xs.end(); it++) {
    if ((*min_it)->freq > (*it)->freq) {
      min_it = it;
    }
  }
  return min_it;
}
// --------------------------------------------------------
// Fn: 生成huffman树
auto huffman(list &ds, std::map<char, elem> &rd) {
  std::vector<elem> xs;
  for (auto kv : rd) {
    xs.push_back(kv.second);
  }

  // 按字典序排序
  auto inc = [](elem &a, elem &b) { return a.id < b.id; };
  std::sort(xs.begin(), xs.end(), inc);

  // 构造初始节点
  for (auto x : xs) {
    ds.push_back(new node(x.id, x.freq));
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
    int freq = lc->freq + rc->freq;
    node *p = new node('*', freq);
    p->lc = lc;
    p->rc = rc;

    // 哈夫曼树节点构造完毕, 插入堆中
    ds.push_back(p);
  }

  return ds.front();
}

// --------------------------------------------------------
// Fn: huffman编码
void huffman_encode(node *p, str code, std::map<char, elem> &rd) {
  if (p == nullptr) return;
  if (p->lc == nullptr && p->rc == nullptr) {
    rd[p->id].code = code;
    return;
  }
  // 左子树编码 0, 右子树编码 1
  huffman_encode(p->lc, code + '0', rd);
  huffman_encode(p->rc, code + '1', rd);
}

// --------------------------------------------------------
// Fn: 构建哈夫曼树问题
// 题解: 构建树形结构
void huffman_tree() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/huffman_tree.in", "r", stdin);
#endif

  str s;
  std::getline(std::cin, s);  // 读取一行数据

#if _TESTDATA_
  // close stdin
  fclose(stdin);
#endif

  std::map<char, elem> rd;
  for (auto ch : s) {
    if (rd.count(ch) > 0) {
      rd[ch].freq += 1;
    } else {
      rd[ch] = {ch, 1, ""};
    }
  }

  // 构建huffman树
  list ds;

  // 生成huffman编码
  node *root = huffman(ds, rd);
  huffman_encode(root, "", rd);

  // 打印字符串对应的huffman编码
  for (auto ch : s) {
    std::cout << rd[ch].code << "";
  }
  std::cout << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  huffman_tree();
  return 0;
}