#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

int main(void)
{
    std::ofstream output("primes.txt");

    output << "Hello World!\n";

    output.close();

    return 0;
}
