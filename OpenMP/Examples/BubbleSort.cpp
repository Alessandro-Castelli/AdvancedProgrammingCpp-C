#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>
#include <ctime>
using namespace std;

void fillRandomNumbers(std::vector<int>& arr, int size) {
    // Riempie il vettore con numeri casuali
    for (int i = 0; i < size; ++i) {
        arr.push_back(rand() % 100);  // Modifica 100 se desideri range diverso
    }
}

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void exchange(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSortParallel(std::vector<int>& arr) {
    int n = arr.size();
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
    // Imposta il seed per la generazione casuale dei numeri
    std::srand(std::time(nullptr));

    // Chiedi all'utente di specificare la dimensione dell'input
    int size;
    std::cout << "Inserisci la dimensione dell'input: ";
    std::cin >> size;

    // Crea un vettore di dimensione specificata e riempilo con numeri casuali
    std::vector<int> arr;
    fillRandomNumbers(arr, size);

    // std::cout << "Array prima dell'ordinamento: ";
    // for (int num : arr) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;
    

    vector<int> arr1 = arr;
    vector<int> arr2 = arr;

    cout<<"\n...Calculate Seq Time...\n";
    double start_no_omp = omp_get_wtime();
    // Chiama la funzione di Bubble Sort
    bubbleSort(arr1);
    double stop_no_omp = omp_get_wtime();
    cout << "\nSeq time: " << (stop_no_omp - start_no_omp) << " seconds\n" << endl;




    cout<<"\n...Calculate Par Time...\n";
    double start = omp_get_wtime();
    bubbleSortParallel(arr2);
    double stop = omp_get_wtime();
    cout << "\nSeq time: " << (stop - start) << " seconds\n" << endl;
   
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
    return 0;
}

