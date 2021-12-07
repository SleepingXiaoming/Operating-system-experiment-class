#include <iostream>
#include <vector>
using namespace std;
const int n = 5;                                                                          //进程个数
const int len = 3;                                                                        //资源种类个数
vector<vector<int>> Allocation = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}}; // Allocation矩阵
vector<vector<int>> Need{{7, 4, 3}, {1, 2, 2}, {6, 0, 0}, {0, 1, 1}, {4, 3, 1}};          // Need矩阵
vector<int> Available = {3, 3, 2};                                                        // Available矩阵
vector<int> sequence;                                                                     //安全序列
vector<int> flag(5, 0);                                                                   //标志
vector<int> p1 = {1, 0, 2};                                                               //进程1申请的资源
vector<int> p4 = {3, 3, 0};                                                               //进程4申请的资源
vector<int> p0 = {0, 2, 0};                                                               //进程0申请的资源
void Assignment();                                                                        //赋值函数
void Bank(int request, vector<int> Request);                                              //银行家算法实现
void safe();                                                                              //安全性算法
int check(vector<int> t1, vector<int> t2);                                                //判断t1是否恒大于t2,是返回1
vector<int> Add(vector<int> s1, vector<int> s2);                                          // 返回s1+ s2
vector<int> Mul(vector<int> s1, vector<int> s2);                                          // 返回s1-s2
void Print(vector<vector<int>> a);                                                        //输出二维矩阵
void Print(vector<int> a);                                                                //输出一维矩阵
int main()
{
    cout << "Allocation矩阵为" << endl;
    Print(Allocation);
    cout << endl;
    cout << "Need矩阵为" << endl;
    Print(Need);
    cout << endl;
    cout << "Available矩阵为" << endl;
    Print(Available);
    cout << endl;
    cout << "判断是否为安全方法" << endl;
    safe();
    cout << endl;
    cout << "进程1申请资源的资源为" << endl;
    Print(p1);
    Bank(1, p1);
    cout << endl;
    cout << "进程4申请资源的资源为" << endl;
    Print(p4);
    Bank(4, p4);
    cout << endl;
    cout << "进程0申请资源的资源为" << endl;
    Print(p0);
    Bank(0, p0);
    cout << endl;
    return 0;
}
void safe()
{
    sequence.clear();
    fill(flag.begin(), flag.end(), 0);
    auto allocation = Allocation;
    auto need = Need;
    auto available = Available;
    for (int i = 0; i < need.size(); i++)
        for (int j = 0; j < need.size(); j++)
        {
            if (flag[j])
                continue;
            if (check(available, need[j]))
            {
                available = Add(available, allocation[j]);
                flag[j] = 1;
                sequence.push_back(j);
                break;
            }
        }
    if (sequence.size() == need.size())
    {
        cout << "存在安全序列" << endl;
        cout << "安全序列为:" << endl;
        for (auto qq : sequence)
            cout << qq << " ";
        cout << endl;
    }
    else
        cout << "不存在安全序列" << endl;
    cout << endl;
}
void Bank(int request, vector<int> Request)
{
    int Flag = 0;
    sequence.clear();
    fill(flag.begin(), flag.end(), 0);
    auto allocation = Allocation;
    auto need = Need;
    auto available = Available;
    if (check(Request, Need[request]))
    {
        cout << "申请大于所需，已拒绝" << endl;
        Flag = 0;
    }
    else if (check(Request, Available))
    {
        cout << "所申请大于所剩余的，应该等待" << endl;
        Flag = 0;
    }
    else
    {
        need[request] = Mul(need[request], Request);
        available = Mul(available, Request);
        allocation[request] = Add(allocation[request], Request);
        for (int i = 0; i < need.size(); i++)
            for (int j = 0; j < need.size(); j++)
            {
                if (flag[j])
                    continue;
                if (check(available, need[j]))
                {
                    available = Add(available, allocation[j]);
                    flag[j] = 1;
                    sequence.push_back(j);
                    break;
                }
            }
        if (sequence.size() == need.size())
        {
            cout << "安全" << endl;
            cout << "安全序列为:" << endl;
            for (auto qq : sequence)
                cout << qq << " ";
            cout << endl;
            Flag = 1;
        }
        else
        {
            cout << "不存在安全序列，有风险，无法将资源分配给Request" << endl;
            Flag = 0;
        }
    }
    if (Flag)
    {
        Need[request] = Mul(Need[request], Request);
        Available = Mul(Available, Request);
        Allocation[request] = Add(Allocation[request], Request);
    }
    cout << endl;
    return;
}
int check(vector<int> t1, vector<int> t2) //判断t1是否恒大于等于t2
{
    int ll = t1.size();
    for (int i = 0; i < ll; i++)
        if (t1[i] < t2[i])
            return 0;
    return 1;
}
vector<int> Add(vector<int> s1, vector<int> s2)
{
    int len1 = s1.size();
    vector<int> ww(len1, 0);
    for (int i = 0; i < len1; i++)
        ww[i] = s1[i] + s2[i];
    return ww;
}
vector<int> Mul(vector<int> s1, vector<int> s2)
{
    int len1 = s1.size();
    vector<int> ww(len1, 0);
    for (int i = 0; i < len1; i++)
        ww[i] = s1[i] - s2[i];
    return ww;
}
void Print(vector<vector<int>> a)
{
    for (auto q : a)
    {
        for (auto w : q)
            cout << w << " ";
        cout << endl;
    }
}
void Print(vector<int> a)
{
    for (auto w : a)
        cout << w << " ";
    cout << endl;
}