// --------------------------------------------------------
// File: 车站检票问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 0  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using value = long long;
using array = std::vector<value>;

// --------------------------------------------------------
// 定义对象

// clang-format off
// --------------------------------------------------------
// Fn: 车站检票问题
// 题解: 二分查找
// 首先算出:
//    单窗口最短耗时: 单窗口处理 M 个用户的耗时 SSTC (Single Shortest Time Cost);
// 接着计算:
//    处理时间下限 Low = 0
//    处理时间上限 High = SSTC
//    全局最短时间 STC = SSTC;
// 然后重复执行直到 Low > High:
//    中间耗时: MTC = (Low + High) / 2;
//    然后判断: MTC时间内同时开设 N个窗口, 能否处理完 M 个用户
//    如果可以:
//        High = MTC - 1;
//        STC = Min(STC, MTC)
//    如果不行:
//        Low = MTC + 1;
// clang-format on
void station_ticket() {
#if _TESTDATA_
  // set ./testdata/.../xxx.in -> stdin
  freopen("./testdata/algorithm/station_ticket.in", "r", stdin);
#endif

  usize n, m;  // n个窗口, m个用户
  std::cin >> n >> m;

  array arr(n);  // 窗口

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  // 按照窗口处理速度排序 (升序排列)
  // Lambda: Compare(a, b)
  auto cmp = [](value &a, value &b) -> bool { return a < b; };
  std::sort(arr.begin(), arr.end(), cmp);

  value sstc = arr[0] * m;     // 单窗口最短处理时间
  value low = 0, high = sstc;  // 界定查找时间范围
  value stc = sstc;            // 记录全局最短耗时

  value mtc;  // 中间耗时
  while (low <= high) {
    mtc = (low + high) >> 1;  // low 和 high 中位数
    usize k = 0;  // 统计: MTC时间内, N个窗口能够处理的人数
    for (usize i = 0; i < n; i++) {
      k += mtc / arr[i];
      if (k >= m) break;
    }

    if (k >= m) {
      high = mtc - 1;
      stc = std::min(stc, mtc);
    } else {
      low = mtc + 1;
    }
  }

  std::cout << stc << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  station_ticket();
  return 0;
}