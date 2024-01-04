#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>
#include <ctime>
using namespace std;

void fillRandomNumbers(vector<int>& arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr.push_back(rand() % 100); 
    }
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void exchange(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSortParallel(vector<int>& arr, int t) {
    int n = arr.size();
    omp_set_num_threads(t);
   for (int k = 0; k < n-1; k++) {
        if (k % 2 == 0) {
            #pragma omp parallel for
            for (int i = 0; i < n/2; i++) {
                if (arr[2*i] > arr[2*i+1]) {
                    //#pragma omp critical
                    {
                        exchange(arr[2*i], arr[2*i+1]);
                    }
                }
            }
        } else {
            #pragma omp parallel for
            for (int i = 0; i < n/2-1; i++) {
                if (arr[2*i+1] > arr[2*i+2]) {
                    //#pragma omp critical
                    {
                        exchange(arr[2*i+1], arr[2*i+2]);
                    }
                }
            }
        }
    }
}

int main() {

    srand(time(nullptr));

    int size;
    cout << "Insert Input: ";
    cin >> size;

    vector<int> arr;
    fillRandomNumbers(arr, size);  

    vector<int> arr1 = arr;
    vector<int> arr2 = arr;

    cout<<"\n...Calculate Seq Time...\n";
    double start_no_omp = omp_get_wtime();

    bubbleSort(arr1);
    double stop_no_omp = omp_get_wtime();
    cout << "\nSeq time: " << (stop_no_omp - start_no_omp) << " seconds\n" << endl;

    for (int t = 1; t<= 12; t++)
    {
        double start = omp_get_wtime();
        bubbleSortParallel(arr2,t);
        double stop = omp_get_wtime();
        cout << "\nPar time, with  " << t << " Threads " << (stop - start) << " seconds\n" << endl;
    
        if(arr1==arr2){
            cout<<"True"<<endl;
        } else {
                cout<<"False"<<endl;
                for (int num : arr1) {
                std::cout << num << " ";
                }
                std::cout << std::endl;

                for (int num : arr2) {
                std::cout << num << " ";
                }
                std::cout << std::endl;
        }
    }
    return 0;
}

