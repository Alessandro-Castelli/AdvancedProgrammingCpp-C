#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class EratosthenesSeries{
    private:
    int maximum;
    vector<bool> primes;

    public:
    EratosthenesSeries(int max);
    void calculateSeries();
    void show();
};

/**
 * This method prints the created series
 */
void EratosthenesSeries::show() {
    cout << "Prime numbers up to: " << maximum << ": ";
    for (int i = 2; i <= maximum; i++) {
        if (primes[i]) {
            std::cout << i << " ";
        }
    }
}

/**
 * This method, given an upper limit, creates a series of Eratosthenes up to that limit.
 * @param max: upper limit
 */
EratosthenesSeries::EratosthenesSeries(int max) {
    this->maximum=max;
    primes.resize(max);
    for (int i=0; i<=max; i++) {
        primes[i]= true;
    }
    primes[0] = false; primes[1]=false;

    for (int p = 2; p * p <= maximum; p++) {
        if (primes[p]) {
            for (int i = p * p; i <= maximum; i += p) {
                primes[i] = false;
            }
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now(); //Start the conometer

    int number = 1000000;
    EratosthenesSeries eratosthenesSeries(number);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end-start;
    cout << "\n" <<"Total time: " << diff.count() << " s\n";

   //eratosthenesSeries.show();

    return 0;
}
