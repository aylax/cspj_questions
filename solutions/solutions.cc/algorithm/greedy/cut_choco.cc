// --------------------------------------------------------
// File: 巧克力切割问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明
struct Splitor;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using Value = int;
using array = std::vector<Splitor>;

// --------------------------------------------------------
// 定义枚举: 切割方式
enum SplitWay {
  horizontal,  // 水平切割
  vertical,    // 垂直切割
};

// 定义对象: 切割
struct Splitor {
  SplitWay sway;  // 切割方式
  Value cost;     // 切割代价
};

// --------------------------------------------------------
// Fn: 巧克力切割问题
// 题解: 贪心算法思想
// 将所有<切割代价>合并后排序
// 优先使用代价大的, 代价计算方式:
// 如果竖直划分, 代价为 vcost * hcounter
// 如果水平划分, 代价为 hcost * vcounter
void cut_choco() {
  usize h, v;  // n 行, m 列

  std::cin >> h >> v;

  array arr(h + v - 2);

  for (usize i = 0; i < h - 1; i++) {
    arr[i].sway = SplitWay::horizontal;
    std::cin >> arr[i].cost;
  }

  for (usize i = h - 1; i < h + v - 2; i++) {
    arr[i].sway = SplitWay::vertical;
    std::cin >> arr[i].cost;
  }

  // 降序排序
  // Lambda: Compare(a, b)
  auto cmp = [](Splitor &a, Splitor &b) -> bool { return a.cost > b.cost; };
  std::sort(arr.begin(), arr.end(), cmp);

  Value total = 0;     // 总计代价
  usize hcounter = 1;  // 记录已经横切的次数
  usize vcounter = 1;  // 记录已经竖切的次数

  for (usize i = 0; i < arr.size(); i++) {
    usize counter;

    // 如果水平划分, 代价为 hcost * vcounter
    if (SplitWay::horizontal == arr[i].sway) {
      counter = vcounter;
      hcounter += 1;
    }

    // 如果竖直划分, 代价为 vcost * hcounter
    if (SplitWay::vertical == arr[i].sway) {
      counter = hcounter;
      vcounter += 1;
    }
    total += arr[i].cost * counter;
  }

  std::cout << total << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  cut_choco();
  return 0;
}