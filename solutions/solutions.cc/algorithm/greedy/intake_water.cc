// --------------------------------------------------------
// File: 排队接水问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明
struct User;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using array = std::vector<User>;

// --------------------------------------------------------
// Struct: 定义取水对象
struct User {
  usize sn;       // 编号
  int take_time;  // 取水花费时间
};

// --------------------------------------------------------
// Fn: 排队接水问题
// 题解: 贪心算法思想
// 取水耗时最多的人最后取水即可
void intake_water() {
  int n;  // 人数
  std::cin >> n;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    arr[i].sn = i + 1;
    std::cin >> arr[i].take_time;
  }

  // 根据接水时间, 升序排序
  // Lambda: Compare(a, b)
  auto cmp = [](User &a, User &b) -> bool { return a.take_time < b.take_time; };
  std::sort(arr.begin(), arr.end(), cmp);

  double total = 0;  // 总花费时间
  for (usize i = 0; i < n; i++) {
    std::cout << arr[i].sn << " ";
    total += arr[i].take_time * (n - 1 - i);
  }

  printf("\n%.2f", total / n);
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  intake_water();
  return 0;
}
