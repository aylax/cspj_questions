// --------------------------------------------------------
// File: 三连击<例生成数字>问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明

// --------------------------------------------------------
// 设定类型别名

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 三连击<例生成数字>问题
// 题解: 枚举思想
void genratio() {
  bool has_result = false;  // 本题是否有解
  int ra, rb, rc;           // ra < rb < rc
  int na, nb, nc;           // 比例系数下 a, b, c的值

  int bucket[10] = {0};  // 创建存储桶, 存入1~9的出现次数
  std::cin >> ra >> rb >> rc;

  // Lambda: 重置数字存储桶
  auto init_bucket = [&bucket]() {
    for (int i = 0; i < 10; i++) {
      bucket[i] = 0;
    }
  };
  // Lambda: 添加数字到桶内
  auto addto_bucket = [&bucket](int num) {
    //  分离每一位数, 存入桶中
    while (num > 0) {
      bucket[num % 10] += 1;
      num /= 10;
    }
  };

  // Lambda: 校验本次录入数据是否通过判定
  auto is_valid = [&bucket]() {
    // 数字只能是 1~9, 不可能出现零
    if (bucket[0] > 0) {
      return false;
    }

    // 如果有任意1~9数字不存在,肯定重复
    for (int i = 1; i < 10; i++) {
      if (bucket[i] == 0) {
        return false;
      }
    }
    return true;
  };

  // 枚举范围
  for (int n = 123; n <= 987; n++) {
    // 数字n 肯定是比例系数的倍数
    if (!(n % ra == 0)) {
      continue;
    }

    // 根据比例系数, 计算a,b,c数值
    int base = n / ra;
    na = base * ra;
    nb = base * rb;
    nc = base * rc;

    // 数值超出3位,后续数字就无需判断
    if (nc > 987 || nb > 987) {
      break;
    }

    // 初始化存储桶
    init_bucket();

    // 存储每个数字出现次数
    addto_bucket(na);
    addto_bucket(nb);
    addto_bucket(nc);

    // 去重判断
    if (is_valid()) {
      has_result = true;
      std::cout << na << " " << nb << " " << nc << "\n";
    }
  }

  // 没有符合条件结果, 输出 "No!!!"
  if (!has_result) {
    std::cout << "No!!!\n";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  genratio();
  return 0;
}
