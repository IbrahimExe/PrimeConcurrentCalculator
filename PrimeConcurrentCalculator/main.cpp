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
            return false;
    }

    return true;
}

int main()
{
    std::cout << "Prime Calculator\n";

    long long testNumbers[] = { 2, 3, 4, 17, 25, 97, 100 };

    for (long long number : testNumbers)
    {
        std::cout << number << (IsPrime(number) ? " is prime.\n" : " is not prime.\n");
    }

    return 0;
}
