// --------------------------------------------------------
// File: 深度优先搜索: 树实现模板
// Require: __cplusplus >= 201402
// --------------------------------------------------------
// Author: zbye
// --------------------------------------------------------
#include <iostream>
#include <stack>
// --------------------------------------------------------
// 预声明

// --------------------------------------------------------
// 设定类型别名

// --------------------------------------------------------
// 定义对象
struct node {
  int val;
  node *left;
  node *right;
};
// --------------------------------------------------------
// Fn: 处理当前节点
void process(node &self) {
  // do sth
  std::cout << "node : " << self.val << "\n";
}

// --------------------------------------------------------
// Fn: 深度优先搜索: 递归实现
// 题解: 先根遍历
void dfs_recursion(node *self) {
  // 节点为空时, 结束访问
  if (self == NULL) return;

  // 处理当前节点
  process(*self);
  // 递归搜索左子节点
  dfs_recursion(self->left);
  // 递归搜索右子节点
  dfs_recursion(self->right);
}

// --------------------------------------------------------
// Fn: 深度优先搜索: 迭代实现
// 题解: 先根遍历, 将子节点压栈
// 对二叉树来说，由于是先序遍历（先遍历当前节点，再遍历左节点，再遍历右节点），所以实现思路如下:
// 对于每个节点来说，
// 先遍历当前节点，然后把右节点压栈，再压左节点
// (这样弹栈的时候会先拿到左节点遍历，符合深度优先遍历要求)
// 接着弹栈，拿到栈顶的节点，
// 如果节点不为空，重复步骤 1， 如果为空，结束遍历。
void dfs_iteration(node *root) {
  // 根节点为空, 则直接返回
  if (root == NULL) return;

  // 创建栈容器, 并压入根节点
  std::stack<node> container;
  container.push(*root);
  // 只要栈中存在元素, 就反复执行
  while (!container.empty()) {
    node self = container.top();
    process(self);

    container.pop();

    // 优先压入右子节点
    if (self.right != NULL) {
      container.push(*self.right);
    }

    // 然后压入左子节点
    if (self.left != NULL) {
      container.push(*self.left);
    }
  }
}

// 构造树
void dfs_test() {
  // 创建节点
  node n0 = {1, NULL, NULL};
  node n1 = {2, NULL, NULL};
  node n2 = {4, NULL, NULL};
  node n3 = {5, NULL, NULL};
  node n4 = {6, NULL, NULL};

  // 串联节点
  n0.left = &n1;
  n0.right = &n2;

  n1.left = &n3;
  n1.right = &n4;

  std::cout << "dfs [recursion]\n";
  dfs_recursion(&n0);
  std::cout << "\n";
  std::cout << "dfs [iteration]: \n";
  dfs_iteration(&n0);
}

// --------------------------------------------------------
// Fn: Main
int main(int argc, char const *argv[]) {
  // std::cout << "c++ standard version: " << __cplusplus << "\n";
  dfs_test();
  return 0;
}