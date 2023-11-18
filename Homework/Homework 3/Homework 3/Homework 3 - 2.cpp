#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Stack{
private:
    vector<T> elements;

public:  
    // Constructor
    Stack() : elements({}) {}

    // Push an element into the stack
    void push(const T& el){
        elements.insert(elements.begin(), el);     
    }

    // Pop the element from the stack
    void pop(){
        if (!elements.empty()) {
            elements.erase(elements.begin());
        }
    }

    // Find and return the maximum element in the stack.
    T findMax() {
        if (elements.empty()) {
            cout<<"Empty stack"<<endl;
            return 0;
        }

        T max = elements[0];
        for (int i = 1; i < elements.size(); ++i) {
            if (max < elements[i]){
                max = elements[i];
            }
        }
        return max;
    }

    //  Get the number of elements currently in the stack.
    int numbOfElements(){
        return elements.size();
    }

    T sum(){
        T s = elements[0];
        for (int i = 1; i < elements.size(); ++i) {
            s = s + elements[i];
        }
        return s;
    }

    // Calculate and return the sum of all elements in the stack.
    void show(){
        for (int i = 0; i < elements.size(); ++i) {
            cout << elements[i] << " ";
        }
            cout << "" << endl;
    }
};


int main(){
    Stack<int> intStack;

    intStack.push(1000);
    intStack.show();
    intStack.push(1);
    intStack.show();
    intStack.push(5);
    intStack.show();
    intStack.push(3);
    intStack.show();
    intStack.pop();
    intStack.show();
    intStack.pop();
    intStack.show();
    intStack.push(10);
    intStack.show();
    intStack.push(100);
    intStack.show();


    int max = intStack.findMax();
    cout<<"The maximum is: "<< max <<endl;

    int numberElements = intStack.numbOfElements();
    cout<<"Number of elements: "<<numberElements<<endl;

    int sumElements = intStack.sum();
    cout<<"Sum of elements: "<<sumElements<<endl;

    cout<<"\n------------------------------------\n"<<endl;

    Stack<double> doubleStack;

    doubleStack.push(1000.12);
    doubleStack.show();
    doubleStack.push(1.98);
    doubleStack.show();
    doubleStack.push(5);
    doubleStack.show();
    doubleStack.push(3.33);
    doubleStack.show();
    doubleStack.pop();
    doubleStack.show();
    doubleStack.pop();
    doubleStack.show();
    doubleStack.push(10.11);
    doubleStack.show();
    doubleStack.push(1001.12);
    doubleStack.show();

    double max2 = doubleStack.findMax();
    cout<<"The maximum is: "<< max2 <<endl;

    double numberElements2 = doubleStack.numbOfElements();
    cout<<"Number of elements: "<<numberElements2<<endl;

    double sumElements2 = doubleStack.sum();
    cout<<"Sum of elements: "<<sumElements2<<endl;

    return 0;
}