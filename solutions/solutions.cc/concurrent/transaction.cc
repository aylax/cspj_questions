// --------------------------------------------------------
// File: 账户交易
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>

// --------------------------------------------------------
// 预声明
// stdin redirect testdata/
#ifndef _TESTDATA_
#define _TESTDATA_ 1  // 1: Open, 0: Close
#endif

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using std::string;

// --------------------------------------------------------
// 定义对象: 账户
struct Account {
 public:
  usize no;        // 编号
  string name;     // 名称
  double balance;  // 余额

  void deposit(double amount) {}

  void withdraw(double amount) {}

  string stringify() {
    string ret;
    ret += "[no: " + std::to_string(no);
    ret += ", name: " + name;
    ret += "] => balance: " + std::to_string(balance);
    ret += "\n";
    return ret;
  }
};

// 定义对象: 交易
struct Transaction {
  usize from;     // 发起交易的账户编号
  usize to;       // 接受交易的账户编号
  double amount;  // 交易金额

  string stringify() {
    string ret;
    ret += "from: " + std::to_string(from);
    ret += ", to: " + std::to_string(to);
    ret += ", amount: " + std::to_string(amount);
    ret += "\n";
    return ret;
  }

  void transfer() {}
};

// --------------------------------------------------------
// Fn:账户交易
void transaction() {
#if _TESTDATA_
  // set ./testdata/.../xxx.in -> stdin
  freopen("./testdata/concurrent/transaction.in", "r", stdin);
#endif

  usize n;  // n 个账户
  std::cin >> n;

  // read accounts
  std::vector<Account> accounts(n);
  for (usize i = 0; i < n; i++) {
    std::cin >> accounts[i].no;
    std::cin >> accounts[i].name;
    std::cin >> accounts[i].balance;
    // std::cout << accounts[i].stringify();
  }

  usize m;  // m笔交易
  std::cin >> m;

  // read transations
  std::vector<Transaction> transations(n);
  for (usize i = 0; i < m; i++) {
    std::cin >> transations[i].from;
    std::cin >> transations[i].to;
    std::cin >> transations[i].amount;
    // std::cout << transations[i].stringify();
  }

  // close stdin
#if _TESTDATA_
  fclose(stdin);
#endif
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  transaction();
  return 0;
}