// --------------------------------------------------------
// File: 快速抢答
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// --------------------------------------------------------
// 预声明
#define _TESTDATA_ 1  // stdin redirect testdata/

struct Player;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using std::string;
using array = std::vector<Player>;
using sysclock = std::chrono::system_clock;

// --------------------------------------------------------
// 定义对象
struct Player {
  usize no;
  string name;
};

// --------------------------------------------------------
// Fn: 快速抢答
// Tip: 一次只能有一个玩家抢到回答的机会
void quickans() {
#ifdef _TESTDATA_
  // set testdata/xxx.in -> stdin
  freopen("./testdata/quickans.in", "r", stdin);
#endif

  // N players
  usize n;
  std::cin >> n;

  // read player name
  array arr(n);
  for (usize i = 0; i < n; i++) {
    arr[i].no = i + 1;
    std::cin >> arr[i].name;
  }

  // close stdin
#ifdef _TESTDATA_
  fclose(stdin);
#endif

  usize delay = 3;  // 3秒倒计时

  // 正式抢答时间
  auto start = sysclock::now() + std::chrono::seconds(delay);

  // Lambda: 倒计时
  auto countdown = [](usize delay) {
    while (delay > 0) {
      std::cout << delay << " seconds left !!\n";
      std::this_thread::sleep_for(std::chrono::seconds(1));
      delay -= 1;
    }
  };

  // Lambda: 显示抢答成功的玩家信息
  auto rush = [](Player who) {
    string desc;
    desc += "[No." + std::to_string(who.no);
    desc += ", " + who.name;
    desc += "] ready to answer !!\n";
    std::cout << desc;
  };

  // Lambda: 准备抢答
  auto ready = [&start, &rush](Player who, std::once_flag *flag) {
    std::this_thread::sleep_until(start);
    std::call_once(*flag, rush, who);
  };

  // add tasks
  std::once_flag flag;
  std::vector<std::thread> jobs;

  // // 加入倒计时
  jobs.push_back(std::thread(countdown, delay));

  // 加入抢答玩家
  for (usize i = 0; i < n; i++) {
    jobs.push_back(std::thread(ready, arr[i], &flag));
  }

  // exec tasks: 主线程会在最后阻塞, 直到全部join的任务完成
  for (usize i = 0; i < jobs.size(); i++) {
    jobs[i].join();
  }
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  quickans();
  return 0;
}