#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class Matrix{
    private:
    vector<vector<int>> matrix;

    public:
        Matrix(int rows, int columns);
        void setElement(int row, int column, int value);
        void show();
        int getNumberRows();
        int getNumberColumns();
        Matrix multiplication(Matrix m);
};

/**
 * @brief Constructor
 * @param rows
 * @param columns
 */
Matrix::Matrix(int rows, int columns) {
    matrix.resize(rows, std::vector<int>(columns));
}

/**
 * @brief This method implements matrix multiplication
 * @param m: matrix
 * @return New matrix which is the multiplication of the previous two or an error message
 */
Matrix Matrix::multiplication(Matrix m) {
    int nRow1 = this->getNumberRows();
    int nCol1 = this->getNumberColumns();
    int nRow2 = m.getNumberRows();
    int nCol2 = m.getNumberColumns();

    if (nCol1 != nRow2){
        cout<<"\n"<<"Unable to perform multiplication because the matrices have unsuitable dimensions."<<endl;
        return *this;
    } else {
        Matrix result(nRow1,nCol2);

        for(int i = 0; i < nRow1; ++i)
            for(int j = 0; j < nCol2; ++j)
                for (int k = 0; k < nCol1; ++k)
                    result.matrix[i][j] += this->matrix[i][k] * m.matrix[k][j];
        return result;
    }
}

/**
 * @brief This method is designed to set a specific element in the matrix to a given value.
 * @param row
 * @param column
 * @param value
 */
void Matrix::setElement(int row, int column, int value){
    matrix[row][column] = value;
}

/**
 * @brief This method is necessary to show a matrix
 */
void Matrix::show() {
    int nRows = this->getNumberRows();
    int nCol= this->getNumberColumns();

    cout<<"Number of rows: "<<nRows<<endl;
    cout<<"Number od columns: "<<nCol<<endl;
    cout<<"Matrix: "<<endl;
    for(int i=0;i<nRows; ++i){
        cout<<"\n"<<endl;
        for (int j = 0; j < nCol ; ++j) {
            cout<< matrix[i][j]<<",";
        }
    }
}
 /**
  *
  * @return The number of matrix's row
  */
int Matrix::getNumberRows(){
    return matrix.size();
}

/**
 *
 * @return The number of matrix's columns
 */
int Matrix::getNumberColumns() {
    return matrix[0].size();
}

int main() {
    auto start = std::chrono::high_resolution_clock::now(); //Start the conometer

    srand(time(0)); // Initializes the random number generator

    int rows1 = 4000; // number of rows in the first matrix
    int cols1 = 8000; // number of columns of the first matrix
    int cols2 = 4000; // number of columns of the second matrix

    Matrix m1(rows1, cols1);
    Matrix m2(cols1, cols2); // the number of rows of the second matrix is equal to the number of columns of the first

    for (int i = 0; i < rows1; ++i)
        for (int j = 0; j < cols1; ++j)
            m1.setElement(i, j, rand() % 100); // sets a random value between 0 and 99

    for (int i = 0; i < cols1; ++i)
        for (int j = 0; j < cols2; ++j)
            m2.setElement(i, j, rand() % 100); // sets a random value between 0 and 99

    Matrix result = m1.multiplication(m2);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << "\n" <<"Total time: " << diff.count() << " s\n";

    cout << "\nMatrix 1:" << endl;
    //m1.show();
    cout << "\nMatrix 2:" << endl;
    //m2.show();
    cout << "\nResult of multiplication:" << endl;
    //result.show();

    return 0;
}
