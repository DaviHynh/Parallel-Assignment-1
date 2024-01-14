#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>

int main(void)
{
    using namespace std::chrono;

    // Starting program timer.
    auto start = high_resolution_clock::now();



    // Ending program timer.
    auto end = high_resolution_clock::now();
    auto executionTime = duration_cast<duration<double>>(end - start);

    // Outputting results.
    std::ofstream output("primes.txt");
    output << "Execution Time: " << executionTime.count() << " Seconds" << std::endl;
    output.close();

    return 0;
}
