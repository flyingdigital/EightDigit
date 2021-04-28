#pragma once

#define N 3
#define SIZE 9

class EightDigit {

public:
	int num[N][N];	// ״̬����
	int depth;		// �����  ��ǰ����
	int value;		// �ܴ���

	int now;	// ��ǰ�ڵ���close��λ�� Ĭ��Ϊ-1
	int parent;	// ���ڵ���close��λ��   ��ǰ�ڵ�ĸ��ڵ�һ����close����

	EightDigit();
	EightDigit(int n[][N], int depth, int value,int now,int parent);
	EightDigit(const EightDigit& e);		// ����constructor

	void swap(int* a, int* b);
	int cost(EightDigit& target);   // ���㵱ǰ�ڵ㵽��ĳ�ڵ�Ĺ��ƴ���
	void location_0(int* a); // ��λ0��λ��
	int move_up(EightDigit& e, EightDigit& target);	// ����  
	int move_right(EightDigit& e, EightDigit& target);	// ����
	int move_down(EightDigit& e, EightDigit& target);	// ����
	int move_left(EightDigit& e, EightDigit& target);	// ����

	int operator==(EightDigit& e);
};
