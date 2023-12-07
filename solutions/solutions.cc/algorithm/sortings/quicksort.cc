// --------------------------------------------------------
// File: 快速排序
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <ctime>
#include <iostream>
#include <vector>

// --------------------------------------------------------
// 预声明
struct Item;

// --------------------------------------------------------
// 设定类型别名
using usize = int;
using Value = int;
using array = std::vector<Item>;

// --------------------------------------------------------
// 定义Item对象
struct Item {
  Value value;

  bool operator>(const Item &other) const {
    const auto &self = (*this);
    return self.value > other.value;
  }
};

// --------------------------------------------------------
// Template: Y Combinator Y运算子
// 用于实现: 在<C++>中递归调用匿名函数
// Example:
//
// auto fib = Y([](auto self, int n) {
//   if (n < 2) return 1;
//   return self(n - 1) + self(n - 2);
// });
//
// fib(5)
//
template <typename Lambda>
struct YCombinator {
  Lambda fn;

  template <typename... Args>
  decltype(auto) operator()(Args &&...args) {  // Passing *this
    return fn(*this, std::forward<Args>(args)...);
  }
};

template <typename Lambda>
decltype(auto) Y(Lambda fn) {  // Wrapper Lambda
  return YCombinator<Lambda>{fn};
}

// --------------------------------------------------------
// Fn: Quick Sort 快速排序 { 基准点随机生成 }, 升序
void quicksort(array &arr) {
  // Lambda: Random Cut Point Fn 生成随机切割点 范围[B, E]
  auto cutfn = [](usize begin, usize end) {
    if (begin > end) std::swap(begin, end);
    std::srand((unsigned)time(NULL));  // 根据当前时间生成随机数
    return begin + (std::rand() % (end - begin + 1));
  };

  // Lambda: Quick Fn 快速排序递归实现
  auto quickfn = Y([&cutfn](auto self, array &arr, usize begin, usize end) {
    if (begin >= end) return;          // 排序结束
    usize low = begin;                 // 初始化低位索引
    usize high = end;                  // 初始化高位索引
    usize cpos = cutfn(begin, end);    // 获取随机切割位置
    std::swap(arr[begin], arr[cpos]);  // 将切割值放在首位
    // 升序排序
    while (low < high) {
      // high索引: 范围中找到小于等于基准值的元素时, 停止
      while (low < high && (arr[high] > arr[begin])) high -= 1;
      // low索引: 范围中找到大于基准值的元素时, 停止
      while (low < high && !(arr[low] > arr[begin])) low += 1;
      std::swap(arr[low], arr[high]);
    }

    // 防止low为无符号整数时, low -1导致的数组越界问题
    low = (low > 0) ? low : 0;

    // 切割值放到正确位置 [...low-1, cutv, low+1...]
    std::swap(arr[begin], arr[low]);
    // 递归排序切割位置左右两侧数据
    self(arr, begin, low - 1);
    self(arr, low + 1, end);
  });
  // Start Quick Sort
  quickfn(arr, 0, arr.size() - 1);
};

void test_quicksort() {
  usize n;
  std::cin >> n;

  array arr(n);
  for (usize i = 0; i < n; i++) {
    std::cin >> arr[i].value;
  }

  quicksort(arr);

  for (usize i = 0; i < n; i++) {
    std::cout << arr[i].value << " ";
  }
  std::cout << "\n";
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  test_quicksort();
  return 0;
}