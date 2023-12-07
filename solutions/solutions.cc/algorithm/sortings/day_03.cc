#include <iostream>
#include <string>
#include <vector>

// 第n个最小的k值
void lesson1() {
  int n, k;  // n个数, 第k个最小数
  std::cin >> n >> k;

  // 输入数据
  std::vector<int> xn(n);
  for (int i = 0; i < n; i++) {
    std::cin >> xn[i];
  }

  // 排序
  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0; j--) {
      if (xn[j] < xn[j - 1]) {
        std::swap<int>(xn[j], xn[j - 1]);
      } else {
        break;
      }
    }
  }

  int bit = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0) {
      bit += 1;
    } else if (xn[i] != xn[i - 1]) {
      bit += 1;
    }

    if (bit == k) {
      std::cout << xn[i];
      return;
    }
  }

  std::cout << "NO RESULT";
}

// 抽卡片问题, 从上到下升序
// TIPS: 该卡牌刚好处于正确位置, 抽卡所需次数就减少1
void lesson2() {
  int n, a[100001];
  std::cin >> n;
  int x = n;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  for (int i = n - 1; i >= 0; i--) {
    if (a[i] == x) {
      x -= 1;
    }
  }
  std::cout << x;
}

// 桶排序
void lesson3() {
  int n, maxsize = 1000;  // 数量
  std::cin >> n;
  // 相同数据装入同一个桶中
  int x, cnt = 0;
  std::vector<int> xn(maxsize, 0);  // 桶的数量取决于最大数的数值
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    if (xn[x] == 0) {
      cnt += 1;
    }
    xn[x] += 1;  // 桶中数量增加1
  }
  std::cout << cnt << "\n";
  // 输出桶内数据
  for (int i = 0; i < maxsize; i++) {
    while (xn[i] > 0) {  // 桶中有数据
      std::cout << i << " ";
      xn[i] -= 1;
    }
  }
}

// 桶排序
int a[101][10001];
void lesson4() {
  int n, m;   // n 选手数量， m 计划录取人数
  int x, y;   // x 报名号,y 分数
  int s = 0;  // 排名靠前的分段人数
  int score;  // 录取最低分数线, 高于该分段全部录取
  std::cin >> n >> m;

  // 存入桶中
  m = m * 150 / 100;  // 最终录取人数 150%
  for (int i = 0; i < n; i++) {
    std::cin >> x >> y;
    a[y][x] += 1;
    a[y][0] += 1;  // 记录该分段人数
  }

  for (int i = 100; i > 0; i--) {
    s += a[i][0];  // 统计排名靠前的分段人数
    if (s >= m) {  // 若所需人数足够
      std::cout << i << " " << s << "\n";
      score = i;  // 录取最低分数线
      break;
    }
  }

  // 打印高于录取最低分数线的数据
  for (int i = 100; i >= score; i--) {
    for (int j = 1000; j < 10000; j++) {
      if (a[i][j] > 0) {
        // 输出 序号 分数
        std::cout << j << " " << i << "\n";
      }
    }
  }
}

// 桶排序
void lesson5() {
  int n, x;  // 人数
  std::cin >> n;
  int maxsize = 121;
  std::vector<int> xn(maxsize);  // 各年龄段人数
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    xn[x] += 1;
  }

  for (int i = 0; i < maxsize; i++) {
    if (xn[i] > 0) {
      std::cout << i << "\n";
    }
  }
}

void lesson6() {
  std::string snum;
  std::cin >> snum;
  int maxsize = 10;
  int bitnum;
  int len = snum.size();
  std::vector<int> xn(maxsize);
  // 存入数据
  for (int i = 0; i < len; i++) {
    bitnum = snum[i] - '0';
    xn[bitnum] += 1;
  }

  // 位数上数字数量
  int bitcnt = 0;
  
  // 最大数
  int maxnum = 0;
  for (int i = maxsize - 1; i >= 0; i--) {
    bitcnt = xn[i];
    while (bitcnt > 0) {
      maxnum = maxnum * 10 + i;
      bitcnt -= 1;
    }
  }

  int minnum = 0;
  for (int i = 1; i < maxsize; i++) {
    bitcnt = xn[i];
    while (bitcnt > 0) {
      minnum = minnum * 10 + i;
      bitcnt -= 1;
    }
  }

  std::cout << (maxnum - minnum) << "\n";
}

int main(int argc, char const *argv[]) {
  lesson6();
  return 0;
}
