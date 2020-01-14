/*
题目描述
把M个同样的苹果放在N个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？
输入
每个用例包含二个整数M和N。0<=m<=10，1<=n<=10。

样例输入
7 3

样例输出(5，1，1和1，5，1 是同一种分法)
8

* 计算放苹果方法数目
* 输入值非法时返回-1
* 1 <= m,n <= 10
* @param m 苹果数目
* @param n 盘子数目数
* @return 放置方法总数
public static int count(int m, int n)

示例1
输入
7 3

输出
8
*/

#include <iostream>
#include <vector>
/*
	试题分析：
	放苹果分两类情况，一种是有盘子为空的， 一种是每个盘子都不为空的
	f(m, n)表示将m个苹果放到n个盘子的不同方法总数，
	1、假设有一个盘子为空(多个为空的包含)， 则f(m, n)=f(m, n-1)
	2、假设每个盘子里面都放有苹果， 则每个盘子上至少有一个苹果， 那么
	剩下m-n个苹果可以转化为， m-n个苹果放到n个盘子上的问题，即f(m, n) = f(m-n, n)
	这两种情况组合起来构成了完备条件，所以f(m, n) = f(m, n-1) + f(m-n, n);
*/
//递归法：
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

//递推法(迭代法)
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
