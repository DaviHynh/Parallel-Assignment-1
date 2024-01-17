#include <iostream>
#include <atomic>
#include <chrono>
#include <fstream>
#include <thread>
#include <vector>

// Function to check if a number is prime.
bool isPrime(int n)
{
    for (int i = 2; i < n - 1; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    std::cout << n << " is prime.\n";

    return true;
}

int main(void)
{
    using namespace std::chrono;

    // Starting program timer.
    auto start = high_resolution_clock::now();


    std::thread t1(isPrime, 12345);
    std::thread t2(isPrime, 123456);
    std::thread t3(isPrime, 174407);

    t1.join();
    t2.join();
    t3.join();


    // Start the counter at 2, since 0 and 1 cannot be prime.
    // Could also make it so that if a number is even, we skip and don't spawn a thread for that number.
    std::atomic<int> counter = 2;

    std::vector<std::thread> pool;

    while (counter < 100)
    {

        // if (threadcount < 8)
        // {
        //     spawn a thread
        // }

        // only issue is that at the end, we need to ensure we finish before finishing main.
        // we need to join or detach.
        // think we need to use join for a thread.

        
        for (auto &t : pool)
        {
            t.join();
        }
    }

    // Need to ensure that the thread count doesn't exceed 8.



    // Could A:
    // Spawn 8 threads at the same time, then join.
    // Or spawn a thread whenever we don't have a total of 8 threads.

    // cant increment a counter after a thread, have to do it before?
    // we assign the counter to a variable, and check it, so yes we do increment it before we spawn a thread.






    // for (int i = 2; i < 10; i++)
    // {
    //     std::cout << n << " is Prime: " << (isPrime(n) ? "True" : "False") << "\n";
    // }


    // maybe you want a while loop, and check if a thread is empty.
    // Create a vector of size 8
    // if a thread is not joinable, remove it, and add another one?
    // So we have a pool to 8 threads, --> while one of them is empty --> start a function with an number and increment it.
    // we can break out of the loop once the 

    // while (!tPool[0].joinable())
    // {

    // }


    // std::thread t1(isPrime, 10);

    // Either give each thread some numbers, or alternate between threads?

    // Maybe at the end of the thread, just place it at the front most of a data structure or something?
    // 



    // // Array for sieve.
    // std::vector<bool> test(100000000, true);

    // // Loop though. (this works for finding prime numbers. now find a way to get it paralleld)
    // for (int i = 2; i < 10000; i++)
    // {
    //     if (test[i] == true)
    //     {
    //         // start a thread here.
    //         // Spawn a thread for a number
    //         // in that thread, calculate and update the array.
    //         // there is an issue with concurrency, and having threads collide
    //         // could use something else to prevent this, so that if the threads to collide, we just move on.


    //         for (int j = i; j < 10000; j++)
    //         {
    //             test[j * i] = false;
    //         }
    //     }
    // }












    // Ending program timer.
    auto end = high_resolution_clock::now();
    auto executionTime = duration_cast<duration<double>>(end - start);

    // Outputting results.
    std::ofstream output("primes.txt");
    output << "Execution Time: " << executionTime.count() << " Seconds" << std::endl;
    output.close();

    return 0;
}
