// --------------------------------------------------------
// File: 混合牛奶问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明
struct Farmer;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using array = std::vector<Farmer>;

// --------------------------------------------------------
// Struct: 定义奶农对象
struct Farmer {
  int unit_price;  // 牛奶单价
  int production;  // 牛奶产量
};

// --------------------------------------------------------
// Fn: 混合牛奶问题
// 题解: 贪心算法思想
// 优先从价格便宜的奶农处收购牛奶
void mixed_milk() {
  int required;  // 需求奶量
  usize n;       // 奶农人数
  std::cin >> required >> n;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i].unit_price;
    std::cin >> arr[i].production;
  }

  // 根据牛奶单价, 升序排序
  // Lambda: Compare(a, b)
  auto cmp = [](Farmer &a, Farmer &b) -> bool {
    return a.unit_price < b.unit_price;
  };
  std::sort(arr.begin(), arr.end(), cmp);

  usize index = 0;  // 从arr[index]奶农处购买牛奶
  int payment = 0;  // 支付金额
  while (required > 0 && index < n) {
    // 按需收购牛奶
    int buying = std::min(required, arr[index].production);
    payment += buying * arr[index].unit_price;

    required -= buying;
    index += 1;
  }
  std::cout << payment << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  mixed_milk();
  return 0;
}
