## 求无向图的BFS序列

### 题目描述

现有 $N$ 个顶点， $M$ 条边的无向图，请输出该无向图的BFS序列，优先遍历编号较小的顶点。

### 输入格式

第 1 行，使用空格隔开的两个整数 $N$ 、 $M$ 

接下来的 $M$ 行，每行 2 个整数 $U_i,V_i$ ，表示边 $(U_i,V_i)$ 。顶点用 1,2,⋯,N 编号。

### 输出格式

该无向图的BFS序列

### 样例

#### 样例输入

```
4 5
1 2
1 4
3 4
1 3
2 4
```

#### 样例输出

```
1 2 3 4
```

### 提示

$1 \le N,M \le 100$