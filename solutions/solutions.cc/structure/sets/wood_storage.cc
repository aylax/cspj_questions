// --------------------------------------------------------
// File: 木材仓库问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <set>
#include <vector>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 0  // 1: Open, 0: Close
#endif

struct line;

// --------------------------------------------------------
// 设定类型别名
using array = std::vector<line>;

// --------------------------------------------------------
// 定义对象
struct line {
  int op;
  int val;
};

// --------------------------------------------------------
// Fn: 升序集合中获取与<给定数值>最相似的元素
// Note: 升序集合(默认), 如果相似度一样, 优先取较小元素
// Tip: set.lower_bound(x) 表示
// 从集合中找出, 第一个<大于或等于x>的元素的位置, 找不到就返回 set.end()
template <typename set, typename set_key_type>
decltype(auto) closest_element(set& xs, const set_key_type& val) {
  // 升序集合, 如果只有一个元素, 就返回开头元素
  const auto find_it = xs.lower_bound(val);
  if (find_it == xs.begin()) return *find_it;

  // 升序集合, 如果没有匹配元素, 就返回末尾元素
  const auto prev_it = std::prev(find_it);
  if (find_it == xs.end()) return *prev_it;

  // 取最相似元素, 如果相似度一样, 优先取较小元素
  const auto diff_lb = val - *prev_it;
  const auto diff_rb = *find_it - val;
  return (diff_lb <= diff_rb) ? *prev_it : *find_it;
}

// --------------------------------------------------------
// Fn: 木材仓库问题
// 题解: 通过集合去除重复元素
void wood_storage() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/wood_storage.in", "r", stdin);
#endif

  int n;
  std::cin >> n;

  array data(n);
  std::set<int> xs;
  for (int i = 0; i < n; i++) {
    std::cin >> data[i].op;
    std::cin >> data[i].val;
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  // Lambda: 添加集合元素
  auto add_then = [&xs](int val) {
    if (xs.count(val) > 0) {
      std::cout << "Already Exist\n";
    } else {
      xs.insert(val);
    }
  };

  // Lambda: 查询集合元素
  auto query_then = [&xs](int val) {
    if (xs.empty()) {
      std::cout << "Empty\n";
    } else {
      auto x = closest_element(xs, val);
      std::cout << x << "\n";
      xs.erase(x);
    }
  };

  for (int i = 0; i < n; i++) {
    auto cur = data[i];
    if (cur.op == 1) {
      add_then(cur.val);
    }
    if (cur.op == 2) {
      query_then(cur.val);
    }
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const* argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  wood_storage();
  return 0;
}