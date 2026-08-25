using System;

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


Console.WriteLine("Prime Calculator using C#");
Console.WriteLine("=================================\n");

long[] testNumbers = { 2, 3, 4, 17, 25, 97, 100 };

foreach (long number in testNumbers)
{
    Console.WriteLine
    (
      $"{number} {(IsPrime(number) ? "is prime." : "is not prime.")}"
    );
}