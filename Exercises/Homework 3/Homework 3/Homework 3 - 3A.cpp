#include <iostream>
#include <string>
#include "Binary.hxx"
using namespace std;

int main() {

    while (true)
    {
        string binary;
        cout << "Enter a positive binary number: ";
        cin >> binary;

        Binary<int> binaryNumber(binary);

        if (binaryNumber.getDecimal() != -1) {
            cout << "Binary Number: " << binary << endl;
            cout << "Decimal equivalent: " << binaryNumber.getDecimal() << endl;
        }
    }
    return 0;
}