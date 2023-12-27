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
struct user;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using value = int;
using array = std::vector<user>;

// --------------------------------------------------------
// 定义取水对象
struct user {
  usize no;    // 编号
  value cost;  // 取水花费时间
};

// --------------------------------------------------------
// Fn: 排队接水问题
// 题解: 贪心算法思想
// 取水耗时最多的人最后取水即可
void intake_water() {
  usize n;  // 人数
  std::cin >> n;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    arr[i].no = i + 1;
    std::cin >> arr[i].cost;
  }

  // 根据接水时间, 升序排序
  // Lambda: Compare(a, b)
  auto cmp = [](user &a, user &b) -> bool { return a.cost < b.cost; };
  std::sort(arr.begin(), arr.end(), cmp);

  double total = 0;  // 总花费时间
  for (usize i = 0; i < n; i++) {
    std::cout << arr[i].no << " ";
    total += arr[i].cost * (n - 1 - i);
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
