# Performance Sieve of Eratosthenes
Below, you will find the results you could see in the terminal when entering an input of 1000000000:

```Bash
  ...Calculate Seq Time...
Seq time: 120.357 seconds

...The Par Time With 1 Thread is: 26.929 seconds
The results are correct.

...The Par Time With 2 Threads is: 26.004 seconds
The results are correct.

...The Par Time With 3 Threads is: 27.372 seconds
The results are correct.

...The Par Time With 4 Threads is: 27.161 seconds
The results are correct.

...The Par Time With 5 Threads is: 27.946 seconds
The results are correct.

...The Par Time With 6 Threads is: 28.702 seconds
The results are correct.

...The Par Time With 7 Threads is: 28.928 seconds
The results are correct.

...The Par Time With 8 Threads is: 29.192 seconds
The results are correct.

...The Par Time With 9 Threads is: 29.725 seconds
The results are correct.

...The Par Time With 10 Threads is: 30.029 seconds
The results are correct.

...The Par Time With 11 Threads is: 35.524 seconds
The results are correct.

...The Par Time With 12 Threads is: 33.14 seconds
The results are correct.
```

As you can see, the time significantly reduces using OpenMP. However, with an increasing number of threads, the performance improvement plateaus, likely due to overhead issues between threads.

# Program Structure and Differences between Sequential and Parallel Code
- The function **eratosthenes(long long int max)** calculates the Sieve of Eratosthenes series in the classic sequential manner.
- The function **eratosthenesPar(long long int n, int t)** calculates the Sieve of Eratosthenes series in a parallel manner.

In the parallel version, some modifications were made to the original code. The `for` loop containing the `.push_back(i);` operation, which is a critical operation, was separated into two distinct loops. This was done to address the critical section in the parallel execution.

