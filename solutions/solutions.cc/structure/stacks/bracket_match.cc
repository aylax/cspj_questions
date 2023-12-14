// --------------------------------------------------------
// File: 括号匹配问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 0  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名
using std::string;
using usize = int;
using value = char;
using stack = std::stack<value>;
using array = std::vector<string>;

// --------------------------------------------------------
// 定义对象

// --------------------------------------------------------
// Fn: 括号匹配问题
// 题解: 就近匹配思路
void bracket_match() {
#if _TESTDATA_
  // set "../testdata/.../xxx.in -> stdin
  freopen("../testdata/structure/bracket_match.in", "r", stdin);
#endif

  usize n;  // 元素个数 n
  std::cin >> n;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif

  const string base = "{[(<}])>";  // 所有括号
  usize half = base.size() >> 1;   // 左右括号分界值

  // dict 存放括号的索引
  std::map<value, usize> dict;
  for (usize i = 0; i < base.size(); i++) {
    value key = base[i];
    dict[key] = i;
  }

  // 括号匹配判断
  auto domatch = [&base, &half, &dict](string &s) -> bool {
    stack bs;
    for (usize i = 0; i < s.size(); i++) {
      value key = s[i];  // 读取字符
      // 如果字符不是括号, 就忽略
      if (dict.count(key) == 0) continue;

      // 如果字符属于左括号(左括号索引都小于half)
      if (dict[key] < half) {
        // 判断括号次序, 只能为 {[(<
        if (!bs.empty() && bs.top() > dict[key]) {
          return false;
        } else {
          bs.push(dict[key]);  // 放入对应的括号索引
        }
      } else {  // 否则如果字符属于右括号
        if (bs.empty() || bs.top() != (dict[key] - half)) {
          return false;
        } else {
          bs.pop();  // 匹配成功, 弹出对应的左括号索引
        }
      }
    }

    // 如果完全匹配的话, bs中不存在元素
    return bs.empty();
  };

  string ans;
  for (usize i = 0; i < n; i++) {
    ans = domatch(arr[i]) ? "YES" : "NO";
    std::cout << ans << "\n";
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  bracket_match();
  return 0;
}