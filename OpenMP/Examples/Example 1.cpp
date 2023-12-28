#include <iostream>
#include <omp.h>
using namespace std;

void simple(long long int n, float *a, float *b) {
    #pragma omp parallel for
    for (long long int i = 1; i < n; i = i + 1) {
        b[i] = (a[i] + a[i - 1]) / 2.0;
    }
}

void verySimple(long long int n, float *a, float *b) {
    for (long long int i = 1; i < n; i = i + 1) {
        b[i] = (a[i] + a[i - 1]) / 2.0;
    }
}

int main() {
    long long int n = 1000000000;  // Esempio: 1000 milioni di elementi
    float *a = new float[n];
    float *b = new float[n];
    for (int x = 0; x < n; x++) {
        a[x] = x + 123456789;
    }

    // Inizio misurazione del tempo senza OpenMP
    double start_no_omp = omp_get_wtime();

    verySimple(n, a, b);

    // Fine misurazione del tempo senza OpenMP
    double stop_no_omp = omp_get_wtime();
    cout << "Tempo senza OpenMP: " << (stop_no_omp - start_no_omp) << " secondi" << endl;

    // Inizio misurazione del tempo con OpenMP
    double start_omp = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            simple(n, a, b);
        }
    }

    // Fine misurazione del tempo con OpenMP
    double stop_omp = omp_get_wtime();
    cout << "Tempo con OpenMP: " << (stop_omp - start_omp) << " secondi" << endl;

    // Deallocazione della memoria
    delete[] a;
    delete[] b;

    return 0;
}
