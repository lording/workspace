#include <iostream>

bool IsPrimeNumber(int n)
{
    if (n <= 1)
    {
        return false;
    }
    for (int i = 2; i < n; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int even;
    while (std::cin >> even)
    {
        int mindiff = even;
        int a = 0, b = 0;
        for (int i = 1; i <= even / 2; i += 2)
        {
            if (!IsPrimeNumber(i) || !IsPrimeNumber(even - i))
            {
                continue;
            }
            int tmp = even - 2 * i;
            if (mindiff > tmp)
            {
                mindiff = tmp;
                a = i;
                b = even - i;
            }
        }
        std::cout << a << std::endl;
        std::cout << b << std::endl;
    }
    return 0;
}