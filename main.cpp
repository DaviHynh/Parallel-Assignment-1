#include <iostream>
#include <atomic>
#include <chrono>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <cmath>


std::mutex myMutex;

int numPrimes = 1;


// Function to check if a number is prime.
bool isPrime(int n)
{
    // Check for a prime number.
    for (int i = 2; i < sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    // Preserves mutual exclusion.
    myMutex.lock();
    numPrimes++;
    myMutex.unlock();

    return true;
}

int main(void)
{
    using namespace std::chrono;

    // Starting program timer.
    auto start = high_resolution_clock::now();


    int num = 3;
    // 100000000
    int total = 100000000;
    std::vector<std::thread> pool;

    // Loop to check all numbers up to total.
    while (num < total)
    {
        // Add threads until we hit 8 threads, or we exceed our count.
        while (num < total && pool.size() < 8)
        {
            if (num % 2 == 0)
            {
                num++;
            }

            std::cout << "Computing: " << num << "\n";

            pool.push_back(std::thread(isPrime, num++));
        }

        // Join each thread after computing for a prime number.
        for (auto &t : pool)
        {
            t.join();
        }

        pool.clear();
    }

    std::cout << "Num Primes: " << numPrimes << "\n";


    // Maybe you spawn 8 threads, and give them all a shared counter.
    // That way, they can each take a number from the counter, and check for a prime number.
    // Each thread will have a while loop? to 100000000.
    // and we join the threads at the end in the main function.

    // 1. Create a vector with 8 threads.
    // 2. Each thread will be given a function.
    // --> This function loops from (shared counter) to 100000000.
    // --> Each thread will access (shared counter), grab a number, up the counter, and then check if the number it grabbed was prime.
    // This way, we aren't spawning and destroying a million threads!








    // Ending program timer.
    auto end = high_resolution_clock::now();
    auto executionTime = duration_cast<duration<double>>(end - start);

    // Outputting results.
    std::ofstream output("primes.txt");
    output << "Execution Time: " << executionTime.count() << " Seconds" << std::endl;
    output.close();

    return 0;
}
