// PrimeConcurrentCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

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
        {
            primeCount++;
        }
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

    long long chunkSize = limit / 4;
    std::cout << "\nSplitting range into 4 chunks:\n";

    for (int i = 0; i < 4; i++)
    {
        long long start = i * chunkSize + 2;
        long long end = (i == 3) ? limit : (i + 1) * chunkSize + 1;

        std::cout << "Chunk " << i + 1 << ": "
            << start << " - " << end << "\n";
    }

    auto startTime = std::chrono::high_resolution_clock::now();

        long long primeCount = CountPrimes(2, limit);

    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

    std::cout << "\nPrimes found: " << primeCount << "\n";
    std::cout << "Time taken: " << elapsedTime.count() << " ms\n";

    return 0;
}
