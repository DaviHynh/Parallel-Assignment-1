// David Huynh
// COP 4520 - Spring, 2024

#include <iostream>
#include <atomic>
#include <chrono>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>

// Counter class to track information on the Sieve of Eratosthenes.
class Counter
{
private:
    std::shared_mutex myMutex;
    std::vector<std::atomic<bool>> primes;
    int num;

public:
    // Constructs a counter with a given range. Sets num to 2 for the sieve.
    Counter(int range) : primes(range)
    {
        num = 2;
    }

    // Returns the bool at the specified position.
    char checkPosition(int position)
    {
        std::shared_lock lock(myMutex);
        return primes[position];
    }

    // Grabs from the counter and increments it.
    int getAndIncrement()
    {
        std::unique_lock lock(myMutex);
        return num++;
    }

    // Sets a position to true. Each bool is atomic, preventing multiple threads from writing at the same time.
    void setTrue(int position)
    {
        primes[position] = true;
    }

    // Returns total primes found, sum primes found, and top ten max primes.
    std::vector<unsigned long int> getInformation()
    {
        int n = primes.size();
        std::vector<unsigned long int> result;

        unsigned long int numOfPrimes = 0;
        unsigned long int sumOfPrimes = 0;

        // Calculates the number of all primes found and their sum.
        for (int i = 2; i < n; i++)
        {
            if (primes[i] == 0)
            {
                numOfPrimes++;
                sumOfPrimes += i;
            }
        }

        result.push_back(numOfPrimes);
        result.push_back(sumOfPrimes);

        // Finds the top 10 max primes.
        for (int i = n - 1; i >= 2; i--)
        {
            if (result.size() < 12 && primes[i] == 0)
            {
                result.push_back(i);
            }
        }

        return result;
    }
};

// Each thread takes a number from the counter, and generates the multiples for it.
void findMultiples(int range, Counter &sharedCounter)
{
    int curr = 0;

    // Loop through the sieve until i^2 < range.
    while (((curr = sharedCounter.getAndIncrement()) * curr) < range)
    {
        // Check if we should generate primes for this number.
        if (sharedCounter.checkPosition(curr) == false)
        {
            // Set all multiples for this number to true.
            for (int i = curr * curr; i < range; i += curr)
            {
                sharedCounter.setTrue(i);
            }
        }
    }
}

// Main function that starts a timer, spawns 8 threads, and prints output to primes.txt.
int main(void)
{
    auto start = std::chrono::high_resolution_clock::now();

    // Calculating 10^8 numbers = 100000000.
    int range = 100000000;
    Counter sharedCounter(range);
    std::vector<std::thread> pool(8);

    // Spawn 8 threads for the Sieve of Eratosthenes.
    for (auto &t : pool)
    {
        t = std::thread(findMultiples, range, std::ref(sharedCounter));
    }

    for (auto &t : pool)
    {
        t.join();
    }

    // Returns necessary information for the output file.
    std::vector<unsigned long int> res = sharedCounter.getInformation();

    // Ending execution timer after threads complete.
    auto end = std::chrono::high_resolution_clock::now();
    auto executionTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    // Outputting results to primes.txt.
    std::ofstream output("primes.txt");

    output << "Execution Time: " << executionTime.count() << " Seconds, ";
    output << "Total Primes Found: " << res[0] << ", ";
    output << "Sum of Primes Found: " << res[1] << "\n\n";
    output << "Top 10 Max Primes:" << "\n";

    for (int i = res.size() - 1; i >= 2; i--)
    {
        output << res[i] << "\n";
    }

    output.close();

    return 0;
}
