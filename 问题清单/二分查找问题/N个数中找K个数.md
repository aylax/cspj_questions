## N个数中找K个数

### 题目描述

给定 $N$ 个整数和$K$个待查找的整数($M_1, M_2, M_3, ...,M_k$)。

如果待查找的整数在给定的$N$ 个整数中，请输出待查找的整数是数组中第几个元素（从$1$开始计算，第一个元素计$1$而不是$0$）

如果待查找的整数不在给定的$N$个整数内，则输出 $0$。

### 输入格式

第一行 输入两个整数 $N$，$K$ （整数间用空格分隔）。

第二行 从小到大输入 $N$个整数 （整数间用空格分隔）。

第三行 输入 $K$个整数 （整数间用空格分隔）。

### 输出格式

输出为一行，包括 $K$ 个部分，每个部分为题目描述中待查找的元素索引或 $0$，$K$ 个部分之间用一个空格分隔。

### 样例

#### 样例输入

```
3 1
1 4 6
4
```

### 样例输出

```
2
```

### 提示

$N$个整数互不相同

${1 \le K \le N \le 10^{6}}$

${1 \le K_i \le N_i \le 10^{6}}$