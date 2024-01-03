#include <iostream>
#include <omp.h>
#include <vector>
#include <random>
#include <cmath> 
#include <algorithm>
using namespace std;

vector<long long int> eratosthenes(long long int max) {
    vector<bool> is_prime(max, true);
    vector<long long int> primes;

    for (long long int i = 2; i < max; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long int j = i * i; j < max; j += i) {
                is_prime[j] = false;
            }
        }
    }

    return primes;
}

vector<long long int> eratosthenesPar(long long int n,int t) {
    vector<int> prime(n + 1, 1); // Inizializza tutti come numeri primi
    vector<long long int> result;
    const int end_p = sqrt(n);

    omp_set_num_threads(t);
    #pragma omp parallel for
    for (int p = 2; p <= end_p; p++) {
        if (prime[p] == 1) {
            for (int i = p * p; i <= n; i += p) {
                prime[i] = 0; // Segna i multipli di p come non primi
            }
        }
    }


    for (int p = 2; p <= n; p++) {
        if (prime[p] == 1) {
            result.push_back(p);
        }
    }
    return result;
}


int main()
{
    long long int max;
    cout<<"Insert the maximum number of the Eratosthenes series: ";
    cin>>max;


    cout<<"\n\n...Calculate Seq Time...\n";
    double start_no_omp = omp_get_wtime();
    vector<long long int> res = eratosthenes(max);
    double stop_no_omp = omp_get_wtime();
    cout << "\nSeq time: " << (stop_no_omp - start_no_omp) << " seconds\n" << endl;

    for (int t = 1; t<= 12; t++)
    {
        double start = omp_get_wtime();
        vector<long long int> res2 = eratosthenesPar(max,t);
        double stop = omp_get_wtime();
        cout<<"\n\n...The Par Time With "<<t<<" Threads is: "<<stop-start<<"seconds"<<endl;
        // sort(res2.begin(), res2.end());

            if (res == res2) {
                cout << "\n\nThe results are correct.\n\n";
            } else {
                cout << "\n\nError\n\n";
                return 1;
            }
    }


    return 0;
}