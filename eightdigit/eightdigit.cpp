#include"eightdigit.h"


EightDigit::EightDigit() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			this->num[i][j] = 0;

	this->value = 0;
	this->depth = 0;
	this->now = -1;
	this->parent = -1;
}


EightDigit::EightDigit(int n[][N], int depth, int value, int now, int parent) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			this->num[i][j] = n[i][j];

	this->value = value;
	this->depth = depth;
	this->now = now;
	this->parent = parent;
}

EightDigit::EightDigit(const EightDigit& e) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			this->num[i][j] = e.num[i][j];

	this->value = e.value;
	this->depth = e.depth;
	this->now = e.now;
	this->parent = e.parent;
}

void EightDigit::swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int EightDigit::cost(EightDigit& target) {
	int count = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (this->num[i][j] != target.num[i][j])
				count++;
	return count;
}

void EightDigit::location_0(int* a) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (this->num[i][j] == 0){
				*a = i;
				a++;
				*a = j;
			}
}

int EightDigit::move_left(EightDigit& container, EightDigit& target) {

	int axis[2];
	location_0(axis);

	//不能在第一行
	if (axis[1] == 0)
		return 0;

	// 可以移动
	// 复制一份数组 并移动
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			container.num[i][j] = this->num[i][j];
	swap(&container.num[axis[0]][axis[1]], &container.num[axis[0]][axis[1] - 1]);

	container.depth = this->depth + 1;
	container.value = this->depth + 1 + cost(target);
	container.now = -1;
	container.parent = this->now;

	return 1;
}

int EightDigit::move_down(EightDigit& container, EightDigit& target) {

	int axis[2];
	location_0(axis);

	//不能在第一行
	if (axis[0] == 2)
		return 0;

	// 可以移动
	// 复制一份数组
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			container.num[i][j] = this->num[i][j];
	swap(&container.num[axis[0]][axis[1]], &container.num[axis[0] + 1][axis[1]]);
	container.depth = this->depth + 1;
	container.parent =this->now;
	container.now = -1;
	container.value = this->depth + 1 + cost(target);

	return 1;
}

int EightDigit::move_right(EightDigit& container, EightDigit& target) {

	int axis[2];
	location_0(axis);

	//不能在第一行
	if (axis[1] == 2)
		return 0;

	// 可以移动
	// 复制一份数组
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			container.num[i][j] = this->num[i][j];
	swap(&container.num[axis[0]][axis[1]], &container.num[axis[0]][axis[1] + 1]);

	container.depth = this->depth + 1;
	container.parent = this->now;
	container.now = -1;
	container.value = this->depth + 1 + cost(target);

	return 1;
}

int EightDigit::move_up(EightDigit& container, EightDigit& target) {

	int axis[2];
	location_0(axis);

	//不能在第一行
	if (axis[0] == 0)
		return 0;

	// 可以移动
	// 复制一份数组
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			container.num[i][j] = this->num[i][j];
	swap(&container.num[axis[0]][axis[1]], &container.num[axis[0] - 1][axis[1]]);
	container.depth = this->depth + 1;
	container.parent = this->now;
	container.now = -1;
	container.value = this->depth + 1 + cost(target);

	return 1;
}

int EightDigit::operator==(EightDigit& e) {
	// 1相等  0不等
	int flag = 1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (e.num[i][j] != this->num[i][j])
				flag = 0;
		}

	return flag;
}

