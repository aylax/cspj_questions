// --------------------------------------------------------
// File: 均分纸牌问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using value = int;
using array = std::vector<value>;

// --------------------------------------------------------
// Fn: 均分纸牌问题
// 题解: 贪心算法思想
// 1. 第一堆纸牌只能从第二堆获取
// 2. 第一堆均分完以后, 不再参与后续操作
// 3. 此时, 第二堆成为了事实上的第一堆
// 4. 重复上述操作, 直至所有堆均分完毕
void share_poker() {
  usize n;  // 纸牌堆数
  std::cin >> n;
  array arr(n);

  // 记录每一堆的纸牌张数
  value sum = 0;  // 纸牌总数
  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i];
    sum += arr[i];
  }
  value avg = sum / n;  // 均分后每堆纸牌的张数 (Sum 是 N的 整数倍)

  usize cnt = 0;
  for (usize i = 0; i < n - 1; i++) {
    if (arr[i] != avg) {  // 数量和<均分张数>不一致, 就把<差值>移到下一堆
      arr[i + 1] += (arr[i] - avg);  // <差值>与下一堆纸牌数求和
      arr[i] = avg;                  // 当前纸牌堆达成均分
      cnt += 1;                      // 操作次数加1
    }
  }

  std::cout << cnt << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  share_poker();
  return 0;
}