/*
题目描述:https://www.nowcoder.com/questionTerminal/15e41630514445719a942e004edc0a5b?f=discussion
矩阵乘法的运算量与矩阵乘法的顺序强相关。

例如：
A是一个50×10的矩阵，B是10×20的矩阵，C是20×5的矩阵
计算A*B*C有两种顺序：（（AB）C）或者（A（BC）），前者需要计算15000次乘法，后者只需要3500次。

编写程序计算不同的计算顺序需要进行的乘法次数

输入描述:
输入多行，先输入要计算乘法的矩阵个数n，每个矩阵的行数，列数，总共2n的数，最后输入要计算的法则

输出描述:
输出需要进行的乘法次数

示例1
输入
3
50 10
10 20
20 5
(A(BC))
输出
3500

*/
#include <iostream>
#include <vector>
#include <stack>
#include <map>

//矩阵
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