/**
 * I have executed this code multiple times with various initial matrix sizes.
 * For an input where the matrices are of size 2000 x 2000, the sequential execution time is approximately 190 seconds.
 * When transitioning from a sequential implementation to a parallel one, a significant improvement in execution times can be observed. 
 * However, beyond a certain point, the addition of further threads may not lead to a substantial improvement.
 * I executed this code with the number of threads ranging from 1 to 12 (which corresponds to the number of cores on my computer). 
 * Using 2 threads takes approximately 89 seconds to complete, 4 threads take about 50 seconds, 8 threads take around 40 seconds, and 12 threads take about 38 seconds to complete.
*/

#include <iostream>
#include <omp.h>
#include <vector>
#include <random> 
#include <chrono> 
using namespace std;

/**
 * This method takes as input the number of rows and columns I want in the matrix and creates a matrix of the desired size filled with random values ranging from 0 to 99.
*/
vector<vector<int>> makeMatrix(int rows, int columns) {
    
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_int_distribution<int> distribution(0, 99);

    vector<vector<int>> matrix(rows, vector<int>(columns, 0));
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = distribution(gen);
        }
    }

    return matrix;
}

/**
 * This method performs the classic matrix multiplication.
*/
vector<vector<int>> mul(const vector<vector<int>>& MatrixA, const vector<vector<int>>& MatrixB) {

    int r1 = MatrixA.size();
    int c1 = MatrixA[0].size();
    int r2 = MatrixB.size();
    int c2 = MatrixB[0].size();

    vector<vector<int>> result(r1, vector<int>(c2, 0));

    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            for (int k = 0; k < c1; ++k) {
                result[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }

    return result;
}

/**
 * This method calculates the matrix representation using OpenMP.
*/
vector<vector<int>> mulPar(const vector<vector<int>>& MatrixA, const vector<vector<int>>& MatrixB, int t) {

    int r1 = MatrixA.size();
    int c1 = MatrixA[0].size();
    int r2 = MatrixB.size();
    int c2 = MatrixB[0].size();

    vector<vector<int>> result(r1, vector<int>(c2, 0));

    omp_set_num_threads(t);
    #pragma omp parallel for
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            for (int k = 0; k < c1; ++k) {
                #pragma omp atomic
                result[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }

    cout << "Number of threads used: " << omp_get_max_threads() << endl;
    cout << "Number of processors: " << omp_get_num_procs() << endl;
    
    return result;
}


bool compare(const vector<vector<int>> MatrixA, const vector<vector<int>> MatrixB){
    int r1 = MatrixA.size();
    int c1 = MatrixA[0].size();

    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c1; ++j) {
            if (MatrixA[i][j] != MatrixB[i][j]){
                cout<<"\nnella riga "<< i <<" colonna " <<j <<endl;
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int nRows1;
    int nColumns1;

    cout << "Insert number of rows of first matrix: ";
    cin >> nRows1;

    cout << "\n Insert number of columns of first matrix: ";
    cin >> nColumns1;

    int nRows2 = nColumns1;
    int nColumns2;
    cout << "\n The number of rows of the second matrix is " << nColumns1 << ", because the number of columns of the first matrix must be the same as the number of rows of the second matrix.\n";
    
    cout << "\n Insert number of columns of second matrix: ";
    cin >> nColumns2;;

    cout << "\n I fill the matrices with values between 0 and 1000 randomly";

    vector<vector<int>> MatrixA = makeMatrix(nRows1,nColumns1);
    vector<vector<int>> MatrixB = makeMatrix(nRows2,nColumns2);

    cout<<"\n\n...Calculate Seq Time...\n";
    double start_no_omp = omp_get_wtime();
    vector<vector<int>> result = mul(MatrixA,MatrixB);
    double stop_no_omp = omp_get_wtime();


    cout << "\nSeq time: " << (stop_no_omp - start_no_omp) << " seconds" << endl;

    cout<<"\n\n...Calculate Par Time...\n";
    
    
    for (int t = 1; t<= 12; t++)
    {
        double start_yes_omp = omp_get_wtime();
        vector<vector<int>> result2 = mulPar(MatrixA,MatrixB,t);
        double stop_yes_omp = omp_get_wtime();
        cout << "\nPar time: " << (stop_yes_omp - start_yes_omp) << " secondsm with " << t << " threads"<< endl;
        bool b =  compare(result,result2);

        if (b)
        {
        cout<<"\n\nCorrect\n\n";
        } else {
        cout<<"\n\nWrong";
        }
    }
    
    return 0;
}