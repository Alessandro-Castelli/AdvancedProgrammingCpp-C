# Performance Matrix Multiplication
Below, I will present the results obtained with input two large square matrices of size 3000 x 3000.
```Bash
Results

- Seq time: 640.6 seconds

- Par time (1 thread): 675.327 seconds
  Correct

- Par time (2 threads): 367.93 seconds
  Correct

- Par time (3 threads): 298.636 seconds
  Correct

- Par time (4 threads): 245.109 seconds
  Correct

- Par time (5 threads): 218.683 seconds
  Correct

- Par time (6 threads): 201.432 seconds
  Correct

- Par time (7 threads): 179.063 seconds
  Correct

- Par time (8 threads): 160.665 seconds
  Correct

- Par time (9 threads): 152.052 seconds
  Correct

- Par time (10 threads): 149.536 seconds
  Correct

- Par time (11 threads): 145.098 seconds
  Correct

- Par time (12 threads): 141.457 seconds
  Correct
```

What you can see above are the results that you can see in the terminal when you run the program and as you can observe, as the number of threads increases, the execution times decrease. I stopped at 12 because my computer has 12 cores, which seemed like a good number to stop at.

# Program Structure

- The function **makeMatrix(int rows, int columns)** creates a matrix of specified size filled with random values ranging from *0* to *99*.

- The function **mul(const vector<vector<int>>& MatrixA, const vector<vector<int>>& MatrixB)** takes two matrices as input and performs matrix multiplication following the mathematical operations that characterize it.

- The function **mulPar(const vector<vector<int>>& MatrixA, const vector<vector<int>>& MatrixB, int t)** performs matrix multiplication using **OpenMP**, reducing the execution time.

- I created the function **compare(const vector<vector<int>> MatrixA, const vector<vector<int>> MatrixB)** to verify the correctness of the multiplication. 
It takes the matrices resulting from sequential and parallel multiplication and checks if they are equal.
