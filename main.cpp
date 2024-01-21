#include <iostream>
#include <atomic>
#include <chrono>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <cmath>

// Counter class to track information.
class Counter
{
private:
    std::shared_mutex myMutex;
    int num;
    int primesFound;
    std::vector<int> lastTen;

public:
    Counter()
    {
        num = 3;
        primesFound = 1;
    }

    int getAndIncrement()
    {
        std::unique_lock lock(myMutex);
        return num++;
    }

    void updatePrimeCountAndLastTen(int numToAdd)
    {
        std::unique_lock lock(myMutex);
        primesFound++;

        if (lastTen.size() < 10)
        {
            lastTen.push_back(numToAdd);
        }
        else
        {
            lastTen.erase(lastTen.begin());
            lastTen.push_back(numToAdd);
        }
    }

    void printInfo()
    {
        std::cout << "Num: " << num << "\n";
        std::cout << "Primes Found: " << primesFound << "\n";
        std::cout << "Last 10: ";

        for (auto &i : lastTen)
        {
            std::cout << i << " ";
        }

        std::cout << "\n";
    }
};


bool isPrime(int n)
{
    // Check for a prime number.
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

// Counts the total number of primes.
void countPrimes(Counter &sharedCounter, int range)
{
    int curr = 0;

    while ((curr = sharedCounter.getAndIncrement()) < range)
    {
        if ((curr % 2) == 0)
        {
            continue;
        }
        else if (isPrime(curr))
        {
            sharedCounter.updatePrimeCountAndLastTen(curr);
        }
    }
}


int main(void)
{
    using namespace std::chrono;

    // Starting program timer.
    auto start = high_resolution_clock::now();

    // 10^8 Numbers = 100000000
    int range = 100000000;
    Counter sharedCounter;
    std::vector<std::thread> pool(8);

    // Start each thread.
    for (auto &t : pool)
    {
        t = std::thread(countPrimes, std::ref(sharedCounter), range);
    }

    // Join each thread before finishing the program.
    for (auto &t : pool)
    {
        t.join();
    }

    sharedCounter.printInfo();

    // Ending program timer.
    auto end = high_resolution_clock::now();
    auto executionTime = duration_cast<duration<double>>(end - start);

    // Outputting results.
    std::ofstream output("primes.txt");
    output << "Execution Time: " << executionTime.count() << " Seconds" << std::endl;
    output.close();

    return 0;
}
