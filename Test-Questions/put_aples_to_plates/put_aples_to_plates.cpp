/*
��Ŀ����
��M��ͬ����ƻ������N��ͬ��������������е����ӿ��Ų��ţ��ʹ��ж����ֲ�ͬ�ķַ���
����
ÿ������������������M��N��0<=m<=10��1<=n<=10��

��������
7 3

�������(5��1��1��1��5��1 ��ͬһ�ַַ�)
8

* �����ƻ��������Ŀ
* ����ֵ�Ƿ�ʱ����-1
* 1 <= m,n <= 10
* @param m ƻ����Ŀ
* @param n ������Ŀ��
* @return ���÷�������
public static int count(int m, int n)

ʾ��1
����
7 3

���
8
*/

#include <iostream>
#include <vector>
/*
	���������
	��ƻ�������������һ����������Ϊ�յģ� һ����ÿ�����Ӷ���Ϊ�յ�
	f(m, n)��ʾ��m��ƻ���ŵ�n�����ӵĲ�ͬ����������
	1��������һ������Ϊ��(���Ϊ�յİ���)�� ��f(m, n)=f(m, n-1)
	2������ÿ���������涼����ƻ���� ��ÿ��������������һ��ƻ���� ��ô
	ʣ��m-n��ƻ������ת��Ϊ�� m-n��ƻ���ŵ�n�������ϵ����⣬��f(m, n) = f(m-n, n)
	�����������������������걸����������f(m, n) = f(m, n-1) + f(m-n, n);
*/
//�ݹ鷨��
static int Count1(const int m, const int n)
{
	if (m < 0)
	{
		return 0;
	}
	if (m == 1 || n == 1)
	{
		return 1;
	}
	return Count1(m, n - 1) + Count1(m - n, n);
}

//���Ʒ�(������)
static int Count2(const int m, const int n)
{
	std::vector<std::vector<int> > vec(m + 1, std::vector<int>(n + 1, 0));
	for (int i = 0; i < m + 1; ++i)
	{
		vec[i][1] = 1;
	}
	for (int j = 0; j < n + 1; ++j)
	{
		vec[0][j] = 1;
		vec[1][j] = 1;
	}
	for (int i = 2; i < m + 1; ++i)
	{
		for (int j = 1; j < n + 1; ++j)
		{
			vec[i][j] = vec[i][j - 1] + (i >= j ? vec[i - j][j] : 0);
		}
	}
	return vec[m][n];
}


int main()
{
	int m = 0, n = 0;
	while (std::cin >> m >> n)
	{
		std::cout << Count2(m, n) << std::endl;
	}
}
