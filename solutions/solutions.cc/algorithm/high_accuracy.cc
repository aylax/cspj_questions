// --------------------------------------------------------
// Module: High Accuracy Algorithm
// Require: __cplusplus >= 201703
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------

// Includes
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// Alias TypeName
using usize = long;
using std::string;
using slice = std::string_view;

// --------------------------------------------------------
// 设置数组长度若超过 10 ^ 6, 该数组不能在函数内部声明
// 因为这样, 数组就属于局部变量, 会分配到栈上, 造成栈内存溢出
// 解决方式:
//    方式一:
//        声明数组为全局变量
//        int an[10000000];
//    方式二:
//        将数组分配在堆上, 但必须手动回收内存
//        int *an = new int[10000000]
const usize MAX_ARR_LENGTH = 1000000;  // 内存栈上最大数组长度

// --------------------------------------------------------

// 高精度加法 An + Bn
string add(slice an, slice bn);

// 高精度减法 An - Bn
string sub(slice an, slice bn);

// --------------------------------------------------------

// 返回切片长度
usize len(const slice &xn) { return xn.size(); }

// 格式化数字, 去除前导零
// xn_format("0000"); // Return 0
// xn_format("0000101"); // Return 101
slice drop_first_n_zero(slice xn) {
  usize _1st_non_zero_bitXn = 0;  // Xn 首个非零位
  usize lenXn = len(xn);          // Xn 长度
  // 寻找第一个非零字符的位置, 不考虑最后一位数字
  while (xn[_1st_non_zero_bitXn] == '0' && _1st_non_zero_bitXn < (lenXn - 1)) {
    _1st_non_zero_bitXn += 1;
  }
  // 移除前导零
  xn.remove_prefix(_1st_non_zero_bitXn);
  return xn;
}

// 判断An, Bn大小
// An, Bn 比较必须先进行去除前导零的操作
bool xn_less_than(slice xn, slice bn) {
  usize lenXn = len(xn);
  usize lenBn = len(bn);
  return lenXn < lenBn || (lenXn == lenBn && xn < bn);
}

// 从vector指定位置反向输出
string backout(const std::vector<int> &xn, usize bitn) {
  string ret;
  for (auto i = 0; i <= bitn; i++) {
    ret += (xn[bitn - i] + '0');
  }
  return ret;
}

string add(slice an, slice bn) {
  string ret;  // 返回值
  an = drop_first_n_zero(an);
  bn = drop_first_n_zero(bn);

  // 如果 An < Bn, 则交换位置
  if (xn_less_than(an, bn)) {
    std::swap<slice>(an, bn);
  }

  int carry = 0, bitsum = 0;  // 进位标记<十进制>, 每一位的和
  bool canBnAddable = true;   // 访问标记<Bn数组是否可访问>
  usize lenAn = len(an);
  usize lenBn = len(bn);
  usize bitAn, bitBn, bitCn = 0;  // An, Bn, Cn当前处理位的下标
  std::vector<int> cn(lenAn + 1);  // Cn存放An+Bn的结果, Cn长度为 len(An) + 1
  for (auto i = 0; i < lenAn; i++) {  // 从最低位开始计算求和, 存入 bitsum
    bitAn = lenAn - 1 - i;
    bitsum = (an[bitAn] - '0') + carry;

    if (canBnAddable && i < lenBn) {  // 如果Bn本次还有剩余位可计算
      bitBn = lenBn - 1 - i;
      bitsum += (bn[bitBn] - '0');
    } else if (canBnAddable && i >= lenBn) {
      canBnAddable = false;  // 标记Bn处理完成
    }

    cn[bitCn] = bitsum % 10;  // 结果存入当前位
    carry = bitsum / 10;      // 设置进位标记
    bitCn += 1;
  }  // END_FOR

  cn[bitCn] = carry;  // 如果最后一位计算仍有进位, 就进最高位

  // 忽略前导零 (例: 009 + 001 => 010 => 10)
  while (cn[bitCn] == 0 && bitCn > 0) {
    bitCn -= 1;
  }

  // Cn存放顺序是低位到高位, 所以要倒序输出
  ret += backout(cn, bitCn);
  return ret;
}

string sub(slice an, slice bn) {
  string ret;  // 返回值结果
  an = drop_first_n_zero(an);
  bn = drop_first_n_zero(bn);

  // An数值 > Bn数值
  if (xn_less_than(an, bn)) {
    std::swap<slice>(an, bn);
    ret += "-";
  }

  int borrow = 0, bitdiff;   // 借位标记<十进制>, 每一位的差
  bool canBnAddable = true;  // 校验标记<记录Bn数组是否访问结束>
  usize lenAn = len(an);
  usize lenBn = len(bn);
  usize bitAn, bitBn, bitCn = 0;   // An, Bn, Cn当前处理位的下标
  std::vector<int> cn(lenAn + 1);  // Cn: 记录An-Bn每一位的计算结果
  for (auto i = 0; i < lenAn; i++) {
    // 从最低位开始计算: An当前位 和 前一轮进位标记 求差, 存入 diff
    bitAn = lenAn - 1 - i;
    bitdiff = (an[bitAn] - '0') - borrow;
    // 如果 Bn还有剩余位可计算, 就继续加上Bn当前位
    if (canBnAddable && i < lenBn) {
      bitBn = lenBn - 1 - i;
      bitdiff -= (bn[bitBn] - '0');
    } else if (canBnAddable && i >= lenBn) {
      canBnAddable = false;  // Bn 数组处理结束时
    }

    // 结果存入当前位
    cn[bitCn] = (bitdiff + 10) % 10;
    borrow = abs(bitdiff) / 10;  // 重置借位标记
    bitCn += 1;
  }

  // 忽略前导零 (例: 009 - 001 => 008 => 8)
  while (cn[bitCn] == 0 && bitCn > 0) {
    bitCn -= 1;
  }

  // Cn存放顺序是低位到高位, 所以要倒序输出
  ret += backout(cn, bitCn);
  return ret;
}

int test_high_accuracy() {
  std::cout << "\nplease input bignum: A B \n";
  string a, b;
  std::cin >> a >> b;

  std::cout << "(+){a, b}: " << add(a, b) << "\n";
  std::cout << "(-){a, b}: " << sub(a, b) << "\n";
  std::cout << std::endl;
  return 0;
}

int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  test_high_accuracy();
}
