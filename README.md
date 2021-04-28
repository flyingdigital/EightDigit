## 关于A*算法

由于A*算法其实是深度优先和广度优先算法的中和，横向搜索的时候我不用一只搜索到每一层最末端，

纵向搜索的时候如果遇到死胡同(代价过高)可以从放弃扩展该节点转而扩展另一个代价小的节点。



评价函数：F(x)=G(x)+H(x)

- F(x):总代价
- G(x):从当节点到目标节点的一个预估代价。如在一个大的坐标系里从一个点到另一个的点代价(曼哈短距离，欧式距离)。
- H(x):从最初节点到当前节点已经支付的代价，比如在一个树里边，已支付代价可以简单认为是当前节点的树深度。



## 使用A*算法解决八数码问题

问题描述为：在3×3的棋盘，摆有八个棋子，每个棋子上标有1至8的某一数字，不同棋子上标的数字不相同。棋盘上还有一个空格，与空格相邻的棋子可以移到空格中。要求解决的问题是：给出一个初始状态和一个目标状态，找出一种从初始转变成目标状态的移动棋子步数最少的移动步骤。

```
# 关于节点类的设计
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
```

成员变量:

- num\[N][N]: 这个用来存储某一节点的九宫格。
- depth: 记录当树的深度。
- value：记录扩展当前节点的总代价，总代价为树深度加上连个不同节点不同点个数。
- now: 后续会用到一个open\_表和一个close\_表，now即当前节点在close\_表中的位置。
- parent: 父节点在close表位置 。

```
关于open_表和close_表
由于需要进行不断地寻路且寻找到的路不一定是正确的路，所以用了两个表来记录这一过程。
open_表里记录的是可以进行扩展的节点，下一步选择哪一个节点将从这个表选出，这里的open_表需要对里	边的每一个点进行排序，代价最小的点将排到表的表头，每次扩展第一个节点。
close_表里记录的是寻路的路径，包括错误的路径。注意这里的close表记录的不是最短路径。

关于最短路径: 最短路径将由最后一个节点找到，从他的parent一直往上找直到最初节点。
```

成员函数:

- move系列:  当把一个节点添加到了close\_表中后，这一节点的所有可以进行扩展的节点都可应该加入到open\_表中。

什么样的节点可以进行扩展，

- 根据当前节点空白点的位置，比如该空白在九宫格的第一行这个节点显然无法扩展出由该节点空白向上移动后的节点，这种情况必须避免。
- 该节点不能是该节点的父节点。
- 该节点不能在close表和open表里。



```
# 关于main函数
#include"eightdigit.h"
#include <iostream>
#include<vector>
using namespace std;
int START[N][N] = {
    {1,0,3},
    {7,2,4},
    {6,8,5}
};
int TARGET[N][N] = {
    {1,2,3},
    {8,0,4},
    {7,6,5}
};

int inverse_number(EightDigit& e) {
    int count = 0;
    int num1[SIZE];

    int n = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            num1[n] = e.num[i][j];
            n++;
        }

    for (int i = 0; i < SIZE; i++)
        for (int j = i + 1; j < SIZE; j++)
            if (num1[i] > num1[j])
                count++;
    return count;
}

int is_reachable(EightDigit& start, EightDigit& target) {
    // 0 不可达 1 可达
    int inverse_num1 = inverse_number(start);
    int inverse_num2 = inverse_number(target);

    if (inverse_num1 % 2 == inverse_num2 % 2)
        return 0;
    return 1;
}

void insert_open(vector<EightDigit>& v, EightDigit& e) {
    vector<EightDigit>::iterator it;

    if (v.empty())
        v.push_back(e);
    else {
        for (it = v.begin(); it != v.end(); it++) {
            if ((*it).value >= e.value) {
                v.insert(it, e);
                return;
            }
        }
        v.push_back(e);
    }
}

int in_vector(vector<EightDigit>& v, EightDigit& e) {
    vector<EightDigit>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
        if (*it == e)
            return 1;
    return 0;
}

int main()
{
    EightDigit *start = new EightDigit(START,0,0,0,-1);
    EightDigit *target = new EightDigit(TARGET, 0, 0, 0,-1);

    vector<EightDigit> open_;
    vector<EightDigit> close_;
    vector<EightDigit> result_;
    if (!is_reachable(*start, *target)) {
        cout << "不可达" << endl;
    }

    insert_open(open_, *start);

    while (open_.size() != 0) {

        // open表的第一个节点一定会加入close表
        EightDigit n = open_[0];
        n.now = close_.size();

        if (n == *target) {
            n.parent = close_.size() - 1; // 最后一个元素
            close_.push_back(n);
            break;
        }
        else {
            // 把open表第一个元素加入到close表
            
            close_.push_back(n);

            // 把open表第一个元素删除
            vector<EightDigit>::iterator it;
            it = open_.begin();
            open_.erase(it);

            // 上移
            EightDigit* up = new EightDigit;
            if (n.move_up(*up, *target))
                if (!(*up == n) && !in_vector(open_, *up) && !in_vector(close_, *up))
                    insert_open(open_, *up);
            // 下移
            EightDigit* down = new EightDigit;
            if (n.move_down(*down, *target))
                if (!(*down == n) && !in_vector(open_, *down) && !in_vector(close_, *down))
                    insert_open(open_, *down);
            // 左移
            EightDigit* left = new EightDigit;
            if (n.move_left(*left, *target))
                if (!(*left == n) && !in_vector(open_, *left) && !in_vector(close_, *left))
                    insert_open(open_, *left);

            // 右移
            EightDigit* right = new EightDigit;
            if (n.move_right(*right, *target))
                if (!(*right == n) && !in_vector(open_, *right) && !in_vector(close_, *right))
                    insert_open(open_, *right);
        }

    }


    vector<EightDigit>::iterator ito;
    cout << "close_" << endl;
    int xx = 1;
    for (ito = close_.begin(); ito != close_.end(); ito++) {
        cout << "第" << xx << "次寻路：" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << ito->num[i][j];
            cout << endl;
        }
        xx++;
    }


    cout << "最短路径:: " << endl;

    EightDigit x = close_[close_.size() - 1];
    while(x.parent != -1){
        result_.push_back(x);
        x = close_[x.parent];
    }

    vector<EightDigit>::reverse_iterator ri;

    int xxx = 1;
    for(ri=result_.rbegin();ri!=result_.rend();ri++){
        cout << "第" << xxx << "次移动：" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << ri->num[i][j];
            cout << endl;
        }
        xxx++;
    }
    return 0;
}

```

open_表和close\_本质上是一个vector。前边说到了open\_表里的节点应该按照节点的代价排序。可以使用优先队列，但我觉得使用vector+插入排序就ok。





## 如何运行该程序

为了省事，我把目标节点和初始节点固化到了一个全局变量里(START, TARGET)，使用时更改这两即可。



## 可以进行改进的地方

程序最开始我使用的一个只想父节点的指针来干活(EightDigit*parent)。但是刚从java转到c++，由于析构函数，复制构造函数，复制构造函数三者没有搞明白，导致后来指针乱指情况，遂改为存储节点在close\_的当前位置与父结点的位置。

针对于此项可以进行扩展。