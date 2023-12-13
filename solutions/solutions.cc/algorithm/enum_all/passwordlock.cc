// --------------------------------------------------------
// File: 数字密码锁问题
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
using usize = int;
using array = std::vector<usize>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 数字密码锁问题
// 题解: 枚举思想
void passwordlock() {
  usize n = 0;  // 读取的状态数量
  std::cin >> n;

  usize locklen = 5;  // 密码锁长度

  array lockin(locklen, 0);  // 当前输入的密码锁状态, 数组形式存放
  array lockot(locklen, 0);  // 当前输出的密码锁状态, 数组形式存放
  array inpass(81);          // lockin状态下可能的密码序列

  // Lambda: lockot结果写入inpass
  auto addto_inpass = [&inpass, &locklen](array &lockot) {
    usize passnum = 0;
    for (usize i = 0; i < locklen; i++) {
      passnum = passnum * 10 + lockot[i];
    }
    inpass.push_back(passnum);
  };

  // Lambda: 生成当前lockin状态下可能的密码序列
  auto gen_inpass_result = [&inpass, &locklen, &lockot,
                            &addto_inpass](array &lockin) {
    inpass.clear();  // 清空inpass的原有生成序列
    // 对密码锁上每一个位置进行拨动
    for (usize i = 0; i < locklen; i++) {
      // 当前位置一次性拨动多少格
      for (usize offset = 1; offset <= 9; offset++) {
        // 方式1: 只拨动一个拨圈
        lockot[i] = (lockin[i] + offset) % 10;
        addto_inpass(lockot);  // 写入输出结果

        if (i + 1 < locklen) {  // 方式2: 同时拨动两个拨圈
          lockot[i + 1] = (lockin[i + 1] + offset) % 10;  // 调整相邻拨圈
          addto_inpass(lockot);                           // 写入输出结果
          lockot[i + 1] = lockin[i + 1];                  // 还原相邻拨圈
        }
      }
      lockot[i] = lockin[i];  // 还原拨圈
    }
  };

  array allpass(100'000);  // 所有可能的密码序列, 初始化0
  for (usize i = 0; i < n; i++) {
    // 读入一行密码状态序列
    for (usize j = 0; j < locklen; j++) {
      std::cin >> lockin[j];  // 初始化当前密码锁输入状态
      lockot[j] = lockin[j];  // 初始化当前密码锁输出状态
    }

    // 生成当前lockin状态下可能的密码序列
    gen_inpass_result(lockin);

    // map映射形式: inpass结果存入allpass表
    for (auto pass : inpass) {
      allpass[pass] += 1;
    }
  }

  usize ans = 0;                 // 正确个数
  for (auto hitnum : allpass) {  // 读取可能全部密码的命中状态次数
    if (hitnum == n) {           // 命中所有密码状态, 即为正确密码
      ans += 1;
    }
  }
  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  passwordlock();
  return 0;
}
