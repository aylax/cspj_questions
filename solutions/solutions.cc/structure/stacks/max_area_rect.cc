// --------------------------------------------------------
// File: :最大的矩形面积问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <stack>
#include <vector>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 0  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名
using usize = long;
using value = long;
using stack = std::stack<usize>;
using array = std::vector<value>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 最大的矩形面积问题
// 题解: 单调栈
void max_area_rect() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/max_area_rect.in", "r", stdin);
#endif

  usize n;  // 元素个数 n
  std::cin >> n;
  array arr(n);  // n个长方形高度

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  stack ms;  // 单调栈

  // Lambda: 求弹出区域的最大矩形面积
  auto max_included = [&ms, &arr](usize r, value k) -> value {
    value ret = 0;
    while (!ms.empty() && arr[ms.top()] >= k) {
      usize m = ms.top();
      ms.pop();
      value h = arr[m];  // 矩形高度
      // 索引L与索引M中间可能存在已弹出的区域(都比H<M>高)
      value l = ms.empty() ? 0 : ms.top() + 1;
      value w = r - l;  // 区域范围
      ret = std::max(ret, w * h);
    }
    return ret;
  };

  // loc 局部最大面积, ans 全局最大面积
  value loc = 0, ans = 0;
  for (usize i = 0; i < n; i++) {
    loc = max_included(i, arr[i]);
    ans = std::max(ans, loc);
    ms.push(i);
  }

  // 求剩余未弹出区域的最大矩形面积
  loc = max_included(n, 0);
  ans = std::max(ans, loc);

  // 输出结果
  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  max_area_rect();
  return 0;
}