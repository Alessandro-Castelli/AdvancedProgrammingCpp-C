# Performance BubbleSort
Below, you will find the results you could see in the terminal when entering an input of: 100000

```bash
Insert Input: 100000

...Calculate Seq Time...

Seq time: 56.355 seconds

Par time, with  1 Threads 45.98 seconds
True

Par time, with  2 Threads 15.395 seconds
True

Par time, with  3 Threads 13.134 seconds
True

Par time, with  4 Threads 12.467 seconds
True

Par time, with  5 Threads 12.973 seconds
True

Par time, with  6 Threads 13.234 seconds
True

Par time, with  7 Threads 15.747 seconds
True

Par time, with  8 Threads 15.312 seconds
True

Par time, with  9 Threads 17.628 seconds
True

Par time, with  10 Threads 16.386 seconds
True

Par time, with  11 Threads 16.307 seconds
True

Par time, with  12 Threads 17.098 seconds
True
```

# Program Structure and Differences between Sequential and Parallel Code

- The function `fillRandomNumbers(vector<int>& arr, int size)` takes a vector of a given size and fills it with random numbers ranging from 0 to 100.

- The function `bubbleSort(vector<int>& arr)` sorts the input array using the **BubbleSort** algorithm in a sequential manner.

- The function `bubbleSortParallel(vector<int>& arr, int t)` sorts the input array using the **BubbleSort** algorithm, but this time in a parallel manner.

In the `bubbleSortParallel(vector<int>& arr, int t)` algorithm, the code is slightly different from the classic algorithm as I separated the *even* cases from the *odd* ones to avoid overhead issues between threads and to achieve better performance.

The best performance is likely achieved with about 4 threads because it represents the optimal compromise between input length and parallelization capability.