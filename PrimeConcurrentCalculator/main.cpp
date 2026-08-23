// PrimeConcurrentCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>

std::mutex primeCountMutex;
long long totalPrimes = 0;

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

void CalculatePrimesThread(long long start, long long end)
{
    long long localPrimeCount = 0;

    for (long long number = start; number <= end; number++)
    {
        if (IsPrime(number))
        {
            localPrimeCount++;
        }
    }

    std::lock_guard<std::mutex> lock(primeCountMutex);
    totalPrimes += localPrimeCount;
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

    const int threadCount = 4;
    long long chunkSize = limit / threadCount;

    totalPrimes = 0;

    std::vector<std::thread> threads;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < threadCount; i++)
    {
        long long start = (i == 0) ? 2 : i * chunkSize + 1;
        long long end = (i == threadCount - 1) ? limit : (i + 1) * chunkSize;

        threads.emplace_back(CalculatePrimesThread, start, end);
    }

    for (std::thread& thread : threads)
    {
        thread.join();
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

    std::cout << "\nThreads used: " << threadCount << "\n";
    std::cout << "Primes found: " << totalPrimes << "\n";
    std::cout << "Time taken: " << elapsedTime.count() << " ms\n";

    return 0;
}