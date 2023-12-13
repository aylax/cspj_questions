// --------------------------------------------------------
// File: 工时管理问题
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明
struct job;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using value = int;
using array = std::vector<job>;

// --------------------------------------------------------
// 定义任务对象
struct job {
  value take;      // 任务耗时
  value deadline;  // 任务最迟结束时间

  // 任务最迟开始时间
  value begin() { return deadline - take; }
};

// --------------------------------------------------------
// Fn: 工时管理问题
// 题解: 贪心算法思想
// 首先: <最迟结束时间>靠后的任务, 放在后面完成
// 其次: 当前任务的<最迟结束时间>应该在下一个任务的<最迟开始时间>之前完成
// 所以:
// 更新当前任务: <最迟结束时间> = min(next.start, self.end)
// 计算当前任务: <最迟开始时间> = <最迟结束时间> - <任务耗时>
// 判断当前任务: <最迟开始时间> 小于 0 表示时间不够完成任务, 返回 -1
// 否则继续判断上一个任务
void manage_time() {
  usize n;  // n项工作
  std::cin >> n;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i].take;
    std::cin >> arr[i].deadline;
  }

  // 根据任务最迟结束时间, 降序排序
  // Lambda: Compare(a, b)
  auto cmp = [](job &a, job &b) -> bool { return a.deadline > b.deadline; };
  std::sort(arr.begin(), arr.end(), cmp);

  // <剩余时间>就是完成的任务的<最迟开始时间>
  value free = arr[0].begin();
  for (usize i = 1; i < n; i++) {
    // <当前任务>必须在<下一个任务>的<最迟开始时间>前结束
    value self_deadline = arr[i].deadline;
    value next_begin = arr[i - 1].begin();
    arr[i].deadline = std::min(next_begin, self_deadline);

    // 更新剩余时间
    free = arr[i].begin();
    // 如果剩余时间小于零, 直接结束检查
    if (free < 0) break;
  }
  std::cout << ((free < 0) ? -1 : free) << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  manage_time();
  return 0;
}