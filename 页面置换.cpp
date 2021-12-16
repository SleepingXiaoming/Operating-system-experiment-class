#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;
vector<int> Sequence{4, 3, 2, 1, 4, 3, 5, 4, 3, 2, 1, 5, 0}; //页面序列
vector<int> opt;                                             // OPT算法数组
int opt_count = 0;                                           // OPT算法缺页计数
vector<int> fifo;                                            // FIFO算法数组
int fifo_count = 0;                                          // FIFO算法缺页计数
struct Lru
{
    int l;
    int times = 0;
};               // LRU结构体
vector<Lru> lru; // LRU算法数组
vector<Lru>::iterator it;
int lru_count = 0;                // LRU算法缺页计数
bool check(vector<int> t, int i); //检验i是否存在于数组t之中
bool check(vector<Lru> t, int i);
void add();                      // LRU加一
bool cmp(Lru l1, Lru l2);        //对LRU结构体进行排序
void OPT(vector<int> sequence);  // OPT算法实现
void FIFO(vector<int> sequence); // FIFO算法实现
void LRU(vector<int> sequence);  // LRU算法实现
int main()
{
    cout << "OPT算法" << endl;
    OPT(Sequence);
    printf("OPT算法的缺页率为:%.2lf%\n", opt_count * 100.0 / Sequence.size());
    cout << endl;

    cout << "FIFO算法" << endl;
    FIFO(Sequence);
    printf("FIFO算法的缺页率为:%.2lf%\n", fifo_count * 100.0 / Sequence.size());
    cout << endl;

    cout << "LRU算法" << endl;
    LRU(Sequence);
    printf("LRU算法的缺页率为:%.2lf%\n", lru_count * 100.0 / Sequence.size());
    return 0;
}
bool check(vector<int> t, int i)
{
    for (auto q : t)
    {
        if (q == i)
            return 1;
    }
    return 0;
}
bool check(vector<Lru> t, int i)
{
    for (auto q : t)
    {
        if (q.l == i)
            return 1;
    }
    return 0;
}
bool cmp(Lru l1, Lru l2)
{
    return l1.times < l2.times;
}
void add()
{
    for (int i = 0; i < lru.size(); i++)
        lru[i].times++;
}
void OPT(vector<int> sequence)
{
    int len = sequence.size();
    for (int i = 0; i < len; i++)
    {
        if (check(opt, sequence[i]))
            cout << "命中" << endl;
        else if (opt.size() < 3)
        {
            cout << "发生缺页中断，" << sequence[i] << "号页面调入内存" << endl;
            opt.push_back(sequence[i]);
            opt_count++;
        }
        else
        {
            vector<bool> temp(3, false);
            int c = 0;
            for (int j = i + 1; j < len; j++)
            {
                if (sequence[j] == opt[0])
                {
                    temp[0] = 1;
                    c++;
                }
                else if (sequence[j] == opt[1])
                {
                    temp[1] = 1;
                    c++;
                }
                else if (sequence[j] == opt[2])
                {
                    temp[2] = 1;
                    c++;
                }
                if (c == 2)
                    break;
            }
            for (int iw = 0; iw < 3; iw++)
            {
                if (!temp[iw])
                {
                    cout << "发生页面置换，将" << sequence[i] << "号页面调入内存，" << opt[iw] << "页面调出内存" << endl;
                    opt[iw] = sequence[i];
                    opt_count++;
                    break;
                }
            }
        }
    }
}
void FIFO(vector<int> sequence)
{
    int len = sequence.size();
    for (int i = 0; i < len; i++)
    {
        if (check(fifo, sequence[i]))
            cout << "命中" << endl;
        else if (fifo.size() < 3)
        {
            cout << "发生缺页中断，" << sequence[i] << "号页面调入内存" << endl;
            fifo.push_back(sequence[i]);
            fifo_count++;
        }
        else
        {
            cout << "发生页面置换，将" << sequence[i] << "号页面调入内存，" << fifo[0] << "页面调出内存" << endl;
            for (int w = 0; w < fifo.size() - 1; w++)
                fifo[w] = fifo[w + 1];
            fifo[fifo.size() - 1] = sequence[i];
            fifo_count++;
        }
    }
}
void LRU(vector<int> sequence)
{
    int len = sequence.size();
    for (int i = 0; i < len; i++)
    {
        bool flag = check(lru, sequence[i]);
        if (lru.size() < 3) //页面大小小于3时
        {
            if (!flag) //不存在
            {
                cout << "发生缺页中断" << sequence[i]
                     << "号页面置入内存" << endl;
                lru_count++;
                Lru temp;
                temp.l = sequence[i];
                lru.push_back(temp);
            }
            else
            {
                cout << "命中" << endl;
                for (it = lru.begin(); it != lru.end(); it++)
                {
                    if (it->l == sequence[i])
                        it->times = 0;
                }
            }
        }
        else
        {
            if (!flag) //不存在
            {
                lru_count++;
                Lru temp;
                temp.l = sequence[i];
                cout << "展示" << endl;
                for (auto qq : lru)
                {
                    cout << qq.l << "   " << qq.times << endl;
                }
                cout << endl;
                sort(lru.begin(), lru.end(), cmp);
                cout << "sorted" << endl;
                for (auto qq : lru)
                {
                    cout << qq.l << "   " << qq.times << endl;
                }
                cout << endl;
                cout << "发生缺页中断" << sequence[i]
                     << "号页面置入内存" << lru[2].l << "被调出内存" << endl;
                lru[2] = temp;
            }
            else
            {
                cout << "命中" << endl;
                for (it = lru.begin(); it != lru.end(); it++)
                {
                    if (it->l == sequence[i])
                        it->times = 0;
                }
            }
        }
        add();
    }
}