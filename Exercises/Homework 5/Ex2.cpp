/* Create a console-based application for calculating square root of N, logarithm base 2 of N, and
prime numbers to a given limit N. N should be provided by the user and you should utilize
exceptions defined by you to catch errors at any point in the program. */

#include <iostream>
#include <exception>
#include <cmath>
#include <vector>
using namespace std;

// Custom exception class
class CustomException : public exception {
private:
string message; 

public:
    CustomException(const string& message) : message(message) {}

    // overwrite what() method 
    const char* what() const noexcept override {
    return message.c_str();
  }
};

double squareRoot(double n){
    if(n < 0){
        throw CustomException("Cannot calculate square root of a negative number.");
    }

    return sqrt(n);
}

// Function to calculate the logarithm base 2 of n
double calculateLogBase2(double n) {
    if (n <= 0) {
        throw CustomException("Logarithm base 2 is undefined for non-positive numbers.");
    }
    return log2(n);
}

// Function to calculate if the number is prime
bool isPrime(int n) {
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

// Function to calculate the "n" prime numbers
vector<int> generatePrimes(int n) {
    if (n <= 1){
        throw CustomException("It is mandatory to insert a value of 2 or higher to calcualte the list of primes until n");
    }
    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if (isPrime(i))
            primes.push_back(i);
    return primes;
}

int main(){
    double n;
    cout << "Enter a number (n): ";
    cin >> n;

    try
    {
        double res = squareRoot(n);   
        cout << "Square root of " << n << " is: " << res << endl;

        double res2 = calculateLogBase2(n);
        cout << "Log base 2 of " << n << " is: " << res2 << endl;

        vector<int> res3 = generatePrimes(n);
        cout << "List of primes " ;
        for (int i = 0; i < res3.size(); i++){
            cout << res3[i] << " ";
        }
        
    }
    catch(const CustomException& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}