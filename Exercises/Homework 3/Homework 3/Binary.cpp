#include "Binary.hxx"

template<class T>
bool Binary<T>::isValidBinary(const string& binary) {
    if (binary.length() > 16) {
               return false;
            }


    for (char digit : binary) {
            if (digit != '0' && digit != '1') {
                return false;
            }
        }
        return true;
}

template<class T>
T Binary<T>:: fromStringtoNum(const string& binary) {
        T decimal = 0;

         for (char digit : binary) {
            if (digit == '1') {
                decimal = decimal * 2 + 1;
            } else if (digit == '0') {
                decimal = decimal * 2;
            } 
    }
    return decimal;
}

template<class T>
Binary<T>::Binary(const string& binary) {
        if (isValidBinary(binary)) {
            binaryNumber = binary;
            decimalNumber = fromStringtoNum(binary);
        } else {
            cerr << "Invalid Input" << endl;
            decimalNumber = -1; 
        }
    }

template<class T>
T Binary<T>::getDecimal(){
        return decimalNumber;
}