# COP4520 Programming Assignment 1

### [Documentation](#Program-Documentation)

### [Compile Instructions](#Compile-Instructions)
- #### [Windows on Eustis3](#Compiling-for-Windows-on-Eustis3)
- #### [Mac/Linux on Eustis3](#Compiling-for-Linux-or-Mac-on-Eustis3)
- #### [Local Machine](#Compiling-for-Local-Machine)


## Program Documentation
My program uses the Sieve of Eratosthenes to generate all the prime numbers from 1 to 10^8.
Each of the threads share a counter, and they are each given a unique number.
The threads then check to see if that number is false in the boolean vector.
If the number is false, the thread calculates the multiples for that number, and sets the positions to true in the boolean vector.
If the number is true, the thread moves on to the next number.
At the end, the program loops through the boolean vector to calculate the number of primes, sum of primes, and the top 10 max primes.

The Counter class tracks information about the sieve and includes variables like a shared_mutex, a vector of atomic bool, and an integer num.
The shared_mutex is used to prevent deadlocking and preserve mutual exclusion for the integer num.
Whenever a thread uses the getAndIncrement() method, the shared_mutex locks, and only allows one thread to access num.
When the method finishes, it unlocks, and allows other threads to use that method.

The vector of atomic bool is used so that multiple threads can access the vector at once, but only one thread may read/write into an index.
Using a mutex to lock the entire vector results in a very slow process for updating booleans in the vector.
However, using this approach, we can allow multiple threads to access the vector, but only 1 thread can access an element at a time.
As such, the method setTrue() maintains thread safety, since only one thread may write into a bool at a time preventing data corruption.

The work divided among the 8 threads is approximately equivalent.
If some threads finish calculating multiples earlier than the other threads, they continue to advance the counter and repeat the process.
This continues until the counter reaches 10^8.

Compared to brute force, the Sieve of Eratosthenes runs much more efficiently.
There is less computation for the sieve compared to brute forcing.
However, the space complexity for the sieve is much greater.

When tested for correctness, I used https://t5k.org/howmany.html to check that the number of primes.
I also used http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php to check the last 10 primes.
When I tested with smaller ranges, I received expected results. I also ran multiple tests to try and get a different answer, but they all returned consistent values.

There are some concerns with repeated computation when a thread checks an index set to false, before it is updated by another thread to true.
However, this repeated computation does not affect the final result, since it continues to eliminate multiples.
Additionally, this concern is rarely problematic since each thread begins sequentially, and multiples are often eliminated before the counter increments.

## Compile Instructions
These instructions assume you have a UCF account. To compile without one, check out the third section.

1. If you're not on the campus WiFi, set up the UCF VPN.
2. Download and install Cisco AnyConnect from https://secure.vpn.ucf.edu/.
3. Open Cisco AnyConnect and type in `https://secure.vpn.ucf.edu`.
4. Login to establish a VPN connection.


## Compiling for Windows on Eustis3

0. (If necessary) Set up the UCF VPN.
1. Download and open MobaXterm from https://mobaxterm.mobatek.net/.
2. Establish a new SSH session by clicking `Session --> SSH`.
3. For remote host, input `eustis3.eecs.ucf.edu`.
4. Click `Specify Username` and input your NID (2 letters + numbers).
5. Leave port as 22 and click OK.
6. Double Click `eustis3.eecs.ucf.edu` in the side bar, and login using your password.
7. Download main.cpp from this repository and drag it into the sidebar.
8. Run `g++ main.cpp` and then run `./a.out` on the command line.



## Compiling for Linux or Mac on Eustis3

0. (If necessary) Set up the UCF VPN.
1. Open a terminal window and type `YOURNID@eustis3.eecs.ucf.edu` to connect to eustis3. Use your actual NID instead of YOURNID.
2. Enter your password when prompted for one.
3. Download main.cpp from this repository.
4. Open a NEW terminal, and `cd` into the directory with main.cpp.
5. Transfer that file to eustis3 by doing `scp main.cpp YOUR_NID@eustis3.eecs.ucf.edu:~/`. Retype password when prompted.
6. On the terminal connected to eustis3, `cd` into the directory with main.cpp.
6. Run `g++ main.cpp` and then run `./a.out` on the command line.


## Compiling for Local Machine
This section assumes you don't have a UCF account, and want to compile/run the program.

**Windows/Mac/Linux**
1. Install a g++ compiler to compile C++ files.
2. Download main.cpp from this repository.
3. Use `g++ main.cpp` to compile the program and `./a.out` to run it.

**Quick guide for installing g++:**

Windows --> Enable WSL, setup Ubuntu, run: `sudo apt-get install g++` on its command line.

Linux --> Run `sudo apt-get install g++` on the command line.

MacOS --> Google: `how to install g++ on mac` and follow those steps.


**Other OS**
1. Figure out a way to install the g++ compiler on your OS.
2. Compile main.cpp using `g++ main.cpp` and run it using `./a.out`.
