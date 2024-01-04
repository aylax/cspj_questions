// --------------------------------------------------------
// File:  S1013 木材仓库问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <set>

// --------------------------------------------------------
// 预声明

// --------------------------------------------------------
// 设定类型别名

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Template Fn: get closest element in increasement set
template <typename Set>
auto closest_elem(Set& set, const typename Set::value_type& value)
    -> decltype(set.begin()) {
  const auto it = set.lower_bound(value);
  if (it == set.begin()) return it;

  const auto prev_it = std::prev(it);
  // if the next element is closer to `value` than
  // the previous one is, return the next iterator.
  return (it == set.end() || value - *prev_it <= *it - value) ? prev_it : it;
}

// --------------------------------------------------------
// Fn: 读取写入
void in_or_out(std::set<int>& xs) {
  int op, len;

  std::cin >> op >> len;

  if (op == 1) {
    if (xs.count(len) == 1) {
      std::cout << "Already Exist\n";
    } else {
      xs.insert(len);
    }
  } else if (op == 2) {
    if (xs.empty()) {
      std::cout << "Empty\n";
    } else {
      auto val = *(closest_elem(xs, len));
      std::cout << val << "\n";
      xs.erase(val);
    }
  }
}
// --------------------------------------------------------
// Fn: S1013 木材仓库问题
void wood_storage() {
  int n;
  std::cin >> n;
  std::set<int> xs;

  for (int i = 0; i < n; i++) {
    in_or_out(xs);
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const* argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  wood_storage();
  return 0;
}