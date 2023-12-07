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
struct Job;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using array = std::vector<Job>;

// --------------------------------------------------------
// 定义任务对象
struct Job {
  int take_time;        // 任务花费时间
  int latest_end_time;  // 任务最迟结束时间

  int latest_begin_time() { return latest_end_time - take_time; }
};

// --------------------------------------------------------
// Fn: 工时管理问题
// 题解: 贪心算法思想
// 首先: <最迟结束时间>靠后的任务, 放在后面完成
// 其次: 当前任务的<最迟结束时间>应该在下一个任务的<最迟开始时间>之前完成
// 所以:
// 更新当前任务: <最迟结束时间> = min(next.start, self.end)
// 计算当前任务: <最迟开始时间> = <最迟结束时间> - <任务花费时间>
// 判断当前任务: <最迟开始时间> 小于 0 表示时间不够完成任务, 返回 -1
// 否则继续判断上一个任务
void manage_time() {
  usize n;  // n项工作
  std::cin >> n;
  array arr(n);

  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i].take_time;
    std::cin >> arr[i].latest_end_time;
  }

  // 根据任务最迟结束时间, 降序排序
  // Lambda: Compare(a, b)
  auto cmp = [](Job &a, Job &b) -> bool {
    return a.latest_end_time > b.latest_end_time;
  };
  std::sort(arr.begin(), arr.end(), cmp);

  // <剩余时间>就是完成的任务的<最迟开始时间>
  int extra_time = arr[0].latest_begin_time();
  for (usize i = 1; i < n; i++) {
    // <当前任务>必须在<下一个任务>的<最迟开始时间>前结束
    int selfjob_end_time = arr[i].latest_end_time;
    int nextjob_begin_time = arr[i - 1].latest_begin_time();
    arr[i].latest_end_time = std::min(nextjob_begin_time, selfjob_end_time);

    // 更新剩余时间
    extra_time = arr[i].latest_begin_time();
    // 如果剩余时间小于零, 直接结束检查
    if (extra_time < 0) break;
  }
  std::cout << ((extra_time < 0) ? -1 : extra_time) << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  manage_time();
  return 0;
}