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
    int threadCount;

    std::cout << "Prime Calculator\n";
    std::cout << "================\n\n";
    std::cout << "Enter the upper limit: ";
    std::cin >> limit;

    if (limit < 2)
    {
        std::cout << "number must be greater than or equal to 2!\n";
        return 1;
    }

    std::cout << "enter the number of threads: ";
    std::cin >> threadCount;

    if (threadCount < 1)
    {
        std::cout << "need at least 1 thread!\n";
        return 1;
    }

    long long numbersToProcess = limit - 1;

    if (threadCount > numbersToProcess)
    {
        threadCount = static_cast<int>(numbersToProcess);
    }

    totalPrimes = 0;

    std::vector<std::thread> threads;

    long long chunkSize = numbersToProcess / threadCount;
    long long remainder = numbersToProcess % threadCount;

    long long currentStart = 2;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < threadCount; i++)
    {
        long long currentChunkSize = chunkSize;

        if (i < remainder)
        {
            currentChunkSize++;
        }

        long long currentEnd = currentStart + currentChunkSize - 1;

        threads.emplace_back
        (
            CalculatePrimesThread,
            currentStart,
            currentEnd
        );

        currentStart = currentEnd + 1;
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