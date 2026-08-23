// PrimeConcurrentCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

bool IsPrime(long long number)
{
    if (number <= 1)
    {
        return false;
    }

    if (number <= 3)
    {
        return true;
    }

    if (number % 2 == 0 || number % 3 == 0)
    { 
        return false;
    }
      
    for (long long i = 5; i * i <= number; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
        {
            return false;
        }
    }

    return true;
}

long long CountPrimes(long long start, long long end)
{
    long long primeCount = 0;

    for (long long number = start; number <= end; number++)
    {
        if (IsPrime(number))
            primeCount++;
    }

    return primeCount;
}

int main()
{
    long long limit;

    std::cout << "Prime Calculator\n";
    std::cout << "================\n\n";
    std::cout << "Enter the upper limit: ";
    std::cin >> limit;

    if (limit < 2)
    {
        std::cout << "number must be greater than or equal to 2!\n";
        return 1;
    }

    long long primeCount = CountPrimes(2, limit);

    std::cout << "\nPrimes found: " << primeCount << "\n";

    return 0;
}
