/*
题目描述
https://www.nowcoder.com/questionTerminal/49e772ab08994a96980f9618892e55b6?f=discussion
在计算机中，由于处理器位宽限制，只能处理有限精度的十进制整数加减法，比如在32位宽处理器计算机中，
参与运算的操作数和结果必须在-2^31~2^31-1之间。如果需要进行更大范围的十进制整数加法，需要使用特殊
的方式实现，比如使用字符串保存操作数和结果，采取逐位运算的方式。如下：
9876543210 + 1234567890 = ?
让字符串 num1="9876543210"，字符串 num2="1234567890"，结果保存在字符串 result = "11111111100"。
-9876543210 + (-1234567890) = ?
让字符串 num1="-9876543210"，字符串 num2="-1234567890"，结果保存在字符串 result = "-11111111100"。

要求编程实现上述高精度的十进制加法。
要求实现方法：
public String add (String num1, String num2)
【输入】num1：字符串形式操作数1，如果操作数为负，则num1的前缀为符号位'-'
num2：字符串形式操作数2，如果操作数为负，则num2的前缀为符号位'-'
【返回】保存加法计算结果字符串，如果结果为负，则字符串的前缀为'-'
注：
(1)当输入为正数时，'+'不会出现在输入字符串中；当输入为负数时，'-'会出现在输入字符串中，且一定在输入字符串最左边位置；
(2)输入字符串所有位均代表有效数字，即不存在由'0'开始的输入字符串，比如"0012", "-0012"不会出现；
(3)要求输出字符串所有位均为有效数字，结果为正或0时'+'不出现在输出字符串，结果为负时输出字符串最左边位置为'-'。

输入描述:
输入两个字符串

输出描述:
输出给求和后的结果

示例1
输入
9876543210
1234567890
输出
11111111100
*/


#include <iostream>
#include <string>
#include <stdlib.h>

//同正或者同负
std::string Add(const std::string& str1, const std::string& str2);
//A - B， 且A > B
std::string SubAB(const std::string& strA, const std::string& strB);
//str1 - str2 (str1和str2都是正数)
std::string Sub(const std::string& str1, const std::string& str2);
//高精度整数加法
std::string Caculate(const std::string& str1, const std::string& str2);

int main(int argc, char* argv[])
{
    std::string str1, str2;
    while (std::cin >> str1 >> str2)
    {
        std::cout << Caculate(str1, str2) << std::endl;
    }
    return 0;
}


//同正或者同负
std::string Add(const std::string& str1, const std::string& str2)
{
    int carry = 0;
    std::string res;
    auto riter_str1 = str1.crbegin();
    auto riter_str2 = str2.crbegin();
    while (riter_str1 != str1.crend() && riter_str2 != str2.crend())
    {
        int a = *riter_str1 - '0';
        int b = *riter_str2 - '0';
        int sum = a + b + carry;
        carry = 0;    //置位
        if (sum > 9)
        {
            carry = 1;
            sum = sum - 10;
        }
        res.append(1, '0' + sum);
        ++riter_str1;
        ++riter_str2;
    }

    //获取剩余字符串
    const std::string& str = (riter_str1 != str1.crend()) ? str1 : str2;
    auto iter = (riter_str1 != str1.crend()) ? riter_str1 : riter_str2;
    while (iter != str.crend())
    {
        int a = *iter - '0';
        int sum = a + carry;
        carry = 0;    //置位
        if (sum > 9)
        {
            carry = 1;
            sum = sum - 10;
        }
        res.append(1, '0' + sum);
        ++iter;
    }
    if (carry != 0)
    {
        res.append("1");
    }
    return std::string(res.crbegin(), res.crend());
}

//A - B， 且A > B
std::string SubAB(const std::string& strA, const std::string& strB)
{
    int borrow = 0;
    std::string res;
    auto iterA = strA.crbegin();
    auto iterB = strB.crbegin();
    while (iterA != strA.crend())
    {
        char a = *iterA - '0';
        char b = *iterB - '0';
        int sub = a - b - borrow;
        borrow = 0;
        if (sub < 0)
        {
            sub = abs(sub);
            borrow = 1;
        }
        res.append(1, '0' + sub);
        ++iterA;
        ++iterB;
    }
    return std::string(res.crbegin(), res.crend());
}

//str1 - str2 (str1和str2都是正数)
std::string Sub(const std::string& str1, const std::string& str2)
{
    int isNegative = false;
    if (str1.compare(str2) == 0)
    {
        return "0";
    }

    //如果位数不等，则在高位补零，保证比较大小无误
    std::string strA(str1), strB(str2);
    int diff = strA.size() - strB.size();
    if (diff > 0)
    {
        strB.insert(0, diff, '0');
    }
    else if (diff < 0)
    {
        diff = abs(diff);
        strA.insert(0, diff, '0');
    }

    if(strA.compare(strB) > 0)
    {
        return SubAB(strA, strB);
    }
    return "-" + SubAB(strB, strA);
}

//高精度整数加法
std::string Caculate(const std::string& str1, const std::string& str2)
{
    //正 + 正
    if (isdigit(str1.at(0)) && isdigit(str2.at(0)))
    {
        return Add(str1, str2);
    }
    //负 + 负
    if (!isdigit(str1.at(0)) && !isdigit(str2.at(0)))
    {
        return "-" + Add(str1.substr(1), str2.substr(1));
    }

    //正 + 负 或者 负+ 正， 都处理成 A - B（A、B都为正且A > B）
    if (isdigit(str1.at(0)))
    {
        return Sub(str1, str2.substr(1));
    }
    else
    {
        return Sub(str2, str1.substr(1));
    }
    return "";
}

