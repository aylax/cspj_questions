// --------------------------------------------------------
// File: 回文质数问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <cmath>
#include <iostream>
#include <vector>
// --------------------------------------------------------
// 预声明

// --------------------------------------------------------
// 设定类型别名
using usize = int;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: Min 获取最小值
usize min(usize a, usize b) { return a > b ? b : a; }

// --------------------------------------------------------
// Fn: 回文质数问题
// 题解: 枚举思想
void primepal() {
  usize begin, end;
  std::cin >> begin >> end;

  usize maxpal = 9989899;  // 最大回文素数
  end = min(maxpal, end);

  // Lambda: 翻转数字, 判断是否是回文数
  auto is_pal = [](usize n) {
    usize p = n, r = 0;
    while (p > 0) {
      r = r * 10 + p % 10;
      p = p / 10;
    }
    return r == n;
  };

  // Lambda: 平方根内求素数
  auto is_prime = [](usize n) {
    if (n % 2 == 0) {  // 偶数直接返回, 少开一次平方根
      return false;
    }
    for (usize i = 2; i <= std::sqrt(n); i++) {
      if (n % i == 0) {
        return false;
      }
    }
    return true;
  };

  for (usize n = begin; n <= end; n++) {
    // 优先判断回文数
    if (is_pal(n) && is_prime(n)) {
      std::cout << n << "\n";
    }
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  primepal();
  return 0;
}
