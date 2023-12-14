// --------------------------------------------------------
// File: 最大的矩形面积2问题
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
#define _TESTDATA_ 1  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名
using usize = long;
using value = long;
using stack = std::stack<usize>;
using array = std::vector<int>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 直方图内最大矩形面积
value maxrect(const array &arr) {
  stack ms;  // 单调栈
  usize n = arr.size();

  // Lambda: 求弹出区域的最大矩形面积
  auto max_included = [&ms, &arr](usize r, value k) -> value {
    value ret = 0;
    while (!ms.empty() && arr[ms.top()] >= k) {
      usize m = ms.top();
      ms.pop();
      value h = arr[m];  // 矩形高度
      // 索引L与索引M中间可能存在已弹出的区域(都比H<M>高)
      usize l = ms.empty() ? 0 : ms.top() + 1;
      usize w = r - l;  // 区域范围
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
  return ans;
}

// Fn: 最大的矩形面积2问题
// 题解: 将问题转化为<直方图内求矩形面积>
// 依次生成每一行直方图, 并计算该行最大矩形面积 Loc
// 最终取所有行的最大值 ans = Max(Loc)
// 每一行直方图 H(R)生成方式:
//    如果: n2d[R][C] 值为 1,可以与上一行直方图 H(R-1)[C]连通
//    IF: n2d[R][C] == 1:
//        H(R)[C] = H(R-1)[C] + 1
//    否则: 值为 0, 表示无法连通
//    ELSE:
//        H(R)[C] = 0
void max_area_rect2() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/max_area_rect2.in", "r", stdin);
#endif

  usize n, m;  // n 行, m 列
  std::cin >> n >> m;

  // 定义2维数组
  std::vector<array> n2d(n, array(m));

  // 读入数据
  for (usize r = 0; r < n; r++) {
    for (usize c = 0; c < m; c++) {
      std::cin >> n2d[r][c];
    }
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  array h(m);  // 直方图
  value loc = 0, ans = 0;

  for (usize r = 0; r < n; r++) {
    for (usize c = 0; c < m; c++) {
      bool addable = n2d[r][c] == 1;
      h[c] = addable ? h[c] + 1 : 0;
    }
    loc = maxrect(h);
    ans = std::max(ans, loc);
  }
  std::cout << ans << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  max_area_rect2();
  return 0;
}