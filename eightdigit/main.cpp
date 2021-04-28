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
