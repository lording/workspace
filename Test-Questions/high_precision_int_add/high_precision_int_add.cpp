/*
��Ŀ����
https://www.nowcoder.com/questionTerminal/49e772ab08994a96980f9618892e55b6?f=discussion
�ڼ�����У����ڴ�����λ�����ƣ�ֻ�ܴ������޾��ȵ�ʮ���������Ӽ�����������32λ������������У�
��������Ĳ������ͽ��������-2^31~2^31-1֮�䡣�����Ҫ���и���Χ��ʮ���������ӷ�����Ҫʹ������
�ķ�ʽʵ�֣�����ʹ���ַ�������������ͽ������ȡ��λ����ķ�ʽ�����£�
9876543210 + 1234567890 = ?
���ַ��� num1="9876543210"���ַ��� num2="1234567890"������������ַ��� result = "11111111100"��
-9876543210 + (-1234567890) = ?
���ַ��� num1="-9876543210"���ַ��� num2="-1234567890"������������ַ��� result = "-11111111100"��

Ҫ����ʵ�������߾��ȵ�ʮ���Ƽӷ���
Ҫ��ʵ�ַ�����
public String add (String num1, String num2)
�����롿num1���ַ�����ʽ������1�����������Ϊ������num1��ǰ׺Ϊ����λ'-'
num2���ַ�����ʽ������2�����������Ϊ������num2��ǰ׺Ϊ����λ'-'
�����ء�����ӷ��������ַ�����������Ϊ�������ַ�����ǰ׺Ϊ'-'
ע��
(1)������Ϊ����ʱ��'+'��������������ַ����У�������Ϊ����ʱ��'-'������������ַ����У���һ���������ַ��������λ�ã�
(2)�����ַ�������λ��������Ч���֣�����������'0'��ʼ�������ַ���������"0012", "-0012"������֣�
(3)Ҫ������ַ�������λ��Ϊ��Ч���֣����Ϊ����0ʱ'+'������������ַ��������Ϊ��ʱ����ַ��������λ��Ϊ'-'��

��������:
���������ַ���

�������:
�������ͺ�Ľ��

ʾ��1
����
9876543210
1234567890
���
11111111100
*/


#include <iostream>
#include <string>
#include <stdlib.h>

//ͬ������ͬ��
std::string Add(const std::string& str1, const std::string& str2);
//A - B�� ��A > B
std::string SubAB(const std::string& strA, const std::string& strB);
//str1 - str2 (str1��str2��������)
std::string Sub(const std::string& str1, const std::string& str2);
//�߾��������ӷ�
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


//ͬ������ͬ��
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
        carry = 0;    //��λ
        if (sum > 9)
        {
            carry = 1;
            sum = sum - 10;
        }
        res.append(1, '0' + sum);
        ++riter_str1;
        ++riter_str2;
    }

    //��ȡʣ���ַ���
    const std::string& str = (riter_str1 != str1.crend()) ? str1 : str2;
    auto iter = (riter_str1 != str1.crend()) ? riter_str1 : riter_str2;
    while (iter != str.crend())
    {
        int a = *iter - '0';
        int sum = a + carry;
        carry = 0;    //��λ
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

//A - B�� ��A > B
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

//str1 - str2 (str1��str2��������)
std::string Sub(const std::string& str1, const std::string& str2)
{
    int isNegative = false;
    if (str1.compare(str2) == 0)
    {
        return "0";
    }

    //���λ�����ȣ����ڸ�λ���㣬��֤�Ƚϴ�С����
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

//�߾��������ӷ�
std::string Caculate(const std::string& str1, const std::string& str2)
{
    //�� + ��
    if (isdigit(str1.at(0)) && isdigit(str2.at(0)))
    {
        return Add(str1, str2);
    }
    //�� + ��
    if (!isdigit(str1.at(0)) && !isdigit(str2.at(0)))
    {
        return "-" + Add(str1.substr(1), str2.substr(1));
    }

    //�� + �� ���� ��+ ���� ������� A - B��A��B��Ϊ����A > B��
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

