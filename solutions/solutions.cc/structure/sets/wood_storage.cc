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
#define _TESTDATA_ 1  // 1: Open, 0: Close
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
// Fn: 获取与Val数值最相近的元素, 如果一样近,优先取较小元素
template <typename set, typename key_type>
decltype(auto) closest_elem(set& xs, const key_type& val) {
  const auto next_it = xs.lower_bound(val);
  if (next_it == xs.begin()) return *next_it;

  const auto prev_it = std::prev(next_it);
  if (next_it == xs.end()) return *prev_it;

  const auto diff_lb = val - *prev_it;
  const auto diff_rb = *next_it - val;
  return (diff_lb <= diff_rb) ? *prev_it : *next_it;
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
      auto x = closest_elem(xs, val);
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