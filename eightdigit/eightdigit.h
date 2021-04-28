#pragma once

#define N 3
#define SIZE 9

class EightDigit {

public:
	int num[N][N];	// 状态矩阵
	int depth;		// 树深度  当前代价
	int value;		// 总代价

	int now;	// 当前节点在close表位置 默认为-1
	int parent;	// 父节点在close表位置   当前节点的父节点一定在close表里

	EightDigit();
	EightDigit(int n[][N], int depth, int value,int now,int parent);
	EightDigit(const EightDigit& e);		// 复制constructor

	void swap(int* a, int* b);
	int cost(EightDigit& target);   // 计算当前节点到达某节点的估计代价
	void location_0(int* a); // 定位0的位置
	int move_up(EightDigit& e, EightDigit& target);	// 上移  
	int move_right(EightDigit& e, EightDigit& target);	// 右移
	int move_down(EightDigit& e, EightDigit& target);	// 下移
	int move_left(EightDigit& e, EightDigit& target);	// 左移

	int operator==(EightDigit& e);
};
