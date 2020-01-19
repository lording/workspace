/*
��Ŀ����:https://www.nowcoder.com/questionTerminal/15e41630514445719a942e004edc0a5b?f=discussion
����˷��������������˷���˳��ǿ��ء�

���磺
A��һ��50��10�ľ���B��10��20�ľ���C��20��5�ľ���
����A*B*C������˳�򣺣���AB��C�����ߣ�A��BC������ǰ����Ҫ����15000�γ˷�������ֻ��Ҫ3500�Ρ�

��д������㲻ͬ�ļ���˳����Ҫ���еĳ˷�����

��������:
������У�������Ҫ����˷��ľ������n��ÿ��������������������ܹ�2n�������������Ҫ����ķ���

�������:
�����Ҫ���еĳ˷�����

ʾ��1
����
3
50 10
10 20
20 5
(A(BC))
���
3500

*/
#include <iostream>
#include <vector>
#include <stack>
#include <map>

//����
struct Matrix
{
    Matrix(int x = 0, int y = 0)
        : m_x(x), m_y(y) {}
    int m_x, m_y;
};

int CaculateMultiTimes(std::map<char, Matrix>& matrixMap, const std::string& formatStr)
{
    std::stack<char> symbolStack;
    int count = 0;
    Matrix base;
    for (size_t i = 0; i < formatStr.size(); ++i)
    {
        const char& ch = formatStr.at(i);
        if (ch != ')')
        {
            symbolStack.push(ch);
            continue;
        }
        if (symbolStack.empty())
        {
            return count;
        }
        if (symbolStack.top() != '(' && base.m_x == 0)
        {
            char tmp = symbolStack.top();
            base = matrixMap[tmp];
            symbolStack.pop();
        }
        while (symbolStack.top() != '(')
        {
            Matrix matrix = matrixMap[symbolStack.top()];
            symbolStack.pop();
            count += matrix.m_x * base.m_y * matrix.m_y;
            base.m_x = matrix.m_x;
            base.m_y = base.m_y;
            if (symbolStack.empty())
            {
                return count;
            }
        }
        symbolStack.pop();
    }
    while (!symbolStack.empty())
    {
        if (base.m_x == 0)
        {
            base = matrixMap[symbolStack.top()];
            symbolStack.pop();
            continue;
        }
        Matrix matrix = matrixMap[symbolStack.top()];
        symbolStack.pop();
        count += matrix.m_x * base.m_y * matrix.m_y;
        base.m_x = matrix.m_x;
        base.m_y = base.m_y;
    }
    return count;
}

int main()
{
    int n;
    while (std::cin >> n)
    {
        std::map<char, Matrix> matrixMap;
        for (size_t i = 0; i < n; ++i)
        {
            Matrix matrix;
            std::cin >> matrix.m_x >> matrix.m_y;
            matrixMap['A' + i] = matrix;
        }
        std::string formatStr;
        std::cin >> formatStr;
        std::cout << CaculateMultiTimes(matrixMap, formatStr) << std::endl;
    }
    return 0;
}