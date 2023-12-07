// --------------------------------------------------------
// File: 玩具谜题问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>

// --------------------------------------------------------
// 预声明
struct Toy;
struct Cmd;

// --------------------------------------------------------
// 设定类型别名
using std::string;
using usize = size_t;

// --------------------------------------------------------
// 定义玩具对象
struct Toy {
  usize index;      // 位置索引
  bool is_outside;  // 是否朝外
  string toyname;   // 名称
};

// 定义指令对象
struct Cmd {     // 指令
  bool turn_rt;  // 是否朝右
  usize offset;  // 偏移位数
};

// --------------------------------------------------------
// Fn: 玩具谜题问题
// 题解: 枚举思想
void toycmd() {
  usize toynum, cmdnum;  // 玩具数量, 指令数量
  std::cin >> toynum >> cmdnum;
  std::vector<Toy> ntoy(toynum);
  std::vector<Cmd> ncmd(cmdnum);

  // 录入toynum个玩具
  for (usize i = 0; i < toynum; i++) {
    ntoy[i].index = i;
    std::cin >> ntoy[i].is_outside;
    std::cin >> ntoy[i].toyname;
  }

  // 录入cmdnum条指令
  for (usize i = 0; i < cmdnum; i++) {
    std::cin >> ncmd[i].turn_rt;
    std::cin >> ncmd[i].offset;
  }

  Cmd curcmd = {};       // 当前执行的指令
  usize toynext = 0;     // 指向下一个的玩具的索引
  Toy curtoy = ntoy[0];  // 当前执行指令的小人

  // 循环处理 cmdnum 条指令
  for (usize i = 0; i < cmdnum; i++) {
    curcmd = ncmd[i];
    // 判断是往数组的哪个方向移动
    bool left = !(curtoy.is_outside ^ curcmd.turn_rt);  // 异或取反
    if (left) {
      toynext = (toynum + curtoy.index - curcmd.offset) % toynum;
    } else {
      toynext = (curtoy.index + curcmd.offset) % toynum;
    }
    curtoy = ntoy[toynext];  // 执行完指令后, 前往下一个玩具
  }

  std::cout << curtoy.toyname << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  toycmd();
  return 0;
}
