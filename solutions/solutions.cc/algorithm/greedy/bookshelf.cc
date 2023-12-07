// --------------------------------------------------------
// File: 约翰书架问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using Value = int;
using array = std::vector<Value>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 约翰书架问题
// 题解: 贪心算法思想
// 优先选择高度比较高的奶牛
void bookshelf() {
  usize n;  // n头奶牛
  Value h;  // h总高度
  std::cin >> n >> h;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  // 根据高度, 降序排序
  // Lambda: Compare(a, b)
  auto cmp = [](Value &a, Value &b) -> bool { return a > b; };
  std::sort(arr.begin(), arr.end(), cmp);

  usize index = 0;  // arr[index] 第index头奶牛
  while (h > 0 && index < n) {
    h -= arr[index];
    index += 1;
  }
  std::cout << index << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  bookshelf();
  return 0;
}