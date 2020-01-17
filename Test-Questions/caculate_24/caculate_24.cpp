/*
��Ŀ����:https://www.nowcoder.com/questionTerminal/fbc417f314f745b1978fc751a54ac8cb?f=discussion
��������������4��1-10�����֣�ͨ���Ӽ��˳����õ�����Ϊ24����ʤ��
���룺
4��1-10�����֡�[���������ظ�����ÿ�����ֽ�����ʹ��һ�Σ�����������֤���쳣����]
�����
true or false

��������:
����4��int����

�������:
�����ܷ�õ�24�㣬�����true���������false

ʾ��1
����
7 2 1 10
���
true
*/

#include<iostream>
#include<vector>
using namespace std;
bool is24(vector<double> a, int tot, double result)
{
    if (a.empty())
    {
        return result == tot;
    }
    for (int i = 0; i < a.size(); i++)
    {
        vector<double> b(a);
        b.erase(b.begin() + i);
        if (is24(b, tot, result + a[i])
            || is24(b, tot, result - a[i])
            || is24(b, tot, result * a[i])
            || is24(b, tot, result / a[i]))
            return true;
    }
    return false;
}
int main()
{
    vector<double> a(4, 0);
    while (cin >> a[0] >> a[1] >> a[2] >> a[3])
    {
        if (is24(a, 24, 0))
            cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}