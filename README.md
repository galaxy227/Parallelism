# Parallelism

- What the heck is parallelism?

This project is benchmarking the performance of OpenMP and Threads in the C++ programming language. Build the program using the provided Makefile, then run ```main``` with an optional command-line argument to seed each thread's work.

- What work does each thread do?

Each thread is tasked with the function ```cpp random_work()```, where the goal is to fill a vector with integers in a given range using random number generation. The vector cannot have duplicate values, which forces the function to continue looping until all possible integers are generated. Furthermore, the function takes an integer argument to set the seed of the random number generation, ensuring all threads do equivalent work. Lastly, the number of threads is determined by OpenMP, then matched by C++'s Threads afterward.

- What parameters were selected for each thread's work?

The only variable changed between each measurement was the seeded value to collect a variety of different random numbers. The range of random integers to generate was hard-coded from 0 to 4,999. Each implementation of parallelism was executed using four threads.

- What are the results?

Most benchmarks measured between four to six seconds for both methods of parallelism regardless of which implementation was used. After running the program hundreds of times, we observed C++'s Threads to be roughly 10% faster than OpenMP. Unfortunately,

- What could we do better?

First and foremost, we should record a collection of benchmarks to prove our findings instead of summarizing the results in words. An effective collection of data would be large enough to minimize uncertainty, which makes automating the benchmarking process desirable. Writing code to execute any number of benchmarks, then analyze the results before outputting them to a text file would be ideal.

## TL;DR

Using threads to process ```cpp random_work()``` is usually faster than OpenMP.
