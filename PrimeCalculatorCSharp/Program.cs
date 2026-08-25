// C# Implementation of a Prime Number Calculator

using System;
using System.Diagnostics;
using System.Threading.Tasks;

bool IsPrime(long number)
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

    for (long i = 5; i * i <= number; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
        {
            return false;
        }
    }

    return true;
}
async Task<long> CalculatePrimesAsync(long start, long end)
{
    return await Task.Run(() =>
    {
        long primeCount = 0;

        for (long number = start; number <= end; number++)
        {
            if (IsPrime(number))
            {
                primeCount++;
            }
        }

        return primeCount;
    });
}

async Task<long> RunCalculationAsync(long limit, int taskCount)
{
    long numbersToProcess = limit - 1;
    long chunkSize = numbersToProcess / taskCount;
    long remainder = numbersToProcess % taskCount;

    List<Task<long>> tasks = new();

    long currentStart = 2;

    for (int i = 0; i < taskCount; i++)
    {
        long currentChunkSize = chunkSize;

        if (i < remainder)
        {
            currentChunkSize++;
        }

        long currentEnd = currentStart + currentChunkSize - 1;

        tasks.Add(CalculatePrimesAsync(currentStart, currentEnd));

        currentStart = currentEnd + 1;
    }

    long[] results = await Task.WhenAll(tasks);

    long totalPrimes = 0;

    foreach (long result in results)
    {
        totalPrimes += result;
    }

    return totalPrimes;
}

Console.WriteLine("Prime Calculator using C#");
Console.WriteLine("=================================\n");

Console.Write("Enter the upper limit: ");

if (!long.TryParse(Console.ReadLine(), out long limit) || limit < 2)
{
    Console.WriteLine("Please enter a valid number greater than or equal to 2.");
    return;
}

Console.Write("Enter the number of tasks: ");

if (!int.TryParse(Console.ReadLine(), out int taskCount) || taskCount < 1)
{
    Console.WriteLine("Please enter at least 1 task.");
    return;
}

if (taskCount > limit - 1)
{
    taskCount = (int)(limit - 1);
}

Stopwatch stopwatch = Stopwatch.StartNew();

long totalPrimes = await RunCalculationAsync(limit, taskCount);

stopwatch.Stop();

Console.WriteLine("\nResults");
Console.WriteLine("-------");
Console.WriteLine($"Range: 2 - {limit}");
Console.WriteLine($"Tasks used: {taskCount}");
Console.WriteLine($"Primes found: {totalPrimes}");
Console.WriteLine($"Time taken: {stopwatch.Elapsed.TotalMilliseconds:F2} ms");