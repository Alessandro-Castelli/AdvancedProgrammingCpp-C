/* Define an exception that can identify division with zero in a calculator code and take counter
measures to solve the problem */

#include <iostream>
#include <stdexcept>
using namespace std;


class DivisionByZeroException : public logic_error {
public:
    DivisionByZeroException(const string& message) : logic_error(message) {}
};

class IndeterminateForm : public runtime_error{
public:
    IndeterminateForm(const string& message) : runtime_error(message){}
};

// Division function
double division(double a, double b) {
    if(a == 0 && b == 0){
        throw IndeterminateForm("Indeterminate form");
    }

    if (b == 0) {
        throw DivisionByZeroException("Division by 0");
    }
    return a / b;
}

int main() {
  double x, y, z;
  bool exception_occurred; 
  do {
    exception_occurred = false;
    cout << "Enter two numbers to divide:";
    cin >> x >> y;
    try {
      z = division(x, y);
      cout << "The result of the division is: " << z << endl;
    }
    catch (DivisionByZeroException& e) {
        cout << "Error: " << e.what() << endl; // Show the error message
        exception_occurred = true;
    }
    catch(IndeterminateForm& e) {
        cerr << "Error: " << e.what() << endl; // Show the error message
        exception_occurred = true;
    }
  } while (exception_occurred); // I repeat the loop until the flag is true

  return 0;
}