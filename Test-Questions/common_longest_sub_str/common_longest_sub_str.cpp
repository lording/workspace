/*
��Ŀ����:
https://www.nowcoder.com/questionTerminal/181a1a71c7574266ad07f9739f791506?f=discussion
���������ַ���a,b�е�������Ӵ������ж��������ڽ϶̴������ȳ��ֵ��Ǹ���
��������:
���������ַ���

�������:
�����ظ����ֵ��ַ�

ʾ��1
����
abcdefghijklmnop
abcsafjklmnopqrstuvw

���
jklmnop
*/
#include <iostream>
#include <string>

std::string LongestCommonSubstr(const std::string& str1, const std::string& str2)
{
	std::string maxSubstr;
	for (size_t i = 0; i < str1.length(); ++i)
	{
		for (size_t j = 1; j < str1.length() - i + 1; ++j)
		{
			std::string str(str1, i, j);
			if (str2.find(str) == std::string::npos)
			{
				break;
			}
			if (maxSubstr.length() < str.length())
			{
				maxSubstr = str;
			}
		}
	}
	return maxSubstr;
}

int main()
{
    std::string str1, str2;
	while (std::cin >> str1 >> str2)
	{
		if (str1.length() < str2.length())
		{
			std::cout << LongestCommonSubstr(str1, str2) << std::endl;
		}
		else
		{
			std::cout << LongestCommonSubstr(str2, str1) << std::endl;
		}
	}
	return 0;
}
