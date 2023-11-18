#include <iostream>
using namespace std;

/**
* This class implements a calculator that performs basic operations.
*/
template <class T>
class Calcualtor{
private:
    T num1; // First operand
    T num2; // Second operand
public:
    //Constructor
    Calcualtor(T val1, T val2) : num1(val1),num2(val2){}

    /**
     * Display the values of the two operands.
    */
    void show(){
        cout << "Number 1: " << num1 << endl;
        cout << "Number 2: " << num2 << endl;
    }

    /**
     * Perform addition and display the result.
    */
    void addition(){
        cout<<"addition: "<< num1 + num2 << endl;
    }

    /**
     * Perform subtraction and display the result.
    */
    void subtraction(){
        cout<<"subtraction: "<< num1 - num2 << endl;
    }

    /**
     * Perform multiplication and display the result.
    */
    void multiplication(){
        cout<<"multiplication: "<< num1 * num2 << endl;
    }

    /**
     *  Perform division and display the result.
    */
    void division(){
        if (num2 == 0)
        {   
            cout << "Error: Division by zero" << endl;
        } else {
            cout << "division: "<< num1 / num2 << endl;
        }
    }
};

int main(){
    Calcualtor<int> calcualtor(10,4);
    
    calcualtor.show();
    calcualtor.addition();
    calcualtor.subtraction();
    calcualtor.multiplication();
    calcualtor.division();

    cout<<"------------------------"<<endl;

    Calcualtor<double> dCalculator(10.3,1.5);
    dCalculator.show();
    dCalculator.addition();
    dCalculator.subtraction();
    dCalculator.multiplication();
    dCalculator.division();
}
