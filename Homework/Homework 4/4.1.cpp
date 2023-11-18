/* Create	a	console-based	application	for	sorting	decimal	numbers	using	quick	sort	and	then	
 convert	the	number	to	binary.	You	should	utilize	Object/Function	like	macros. */
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
using namespace std;

// In this section you can see the macros
#define PRINT(str) \
{\
    cout<<str<<endl;\
}

#define SHOW(vec)\
{\
    int i = 0;\
    while(true){\
        if(i >= vec.size()){\
            cout << "\n" <<endl;\
            break;\
        }\
        cout<<vec[i]<<" ";\
        i++;\
    }\
}

#define QUICKSORT(vec) quicksort(vec, 0, vec.size()-1)

#define NUMBEROFBITS 20

// Function to partition the array into two halves
double partition(vector<double>& arr, double low, double high) {
    double pivot = arr[high];
    double i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}


//Quicksort function
void quicksort(vector<double>& arr, double low, double high) {
    if (low < high) {
        // Pivot
        double pivotIndex = partition(arr, low, high);

        // Recursively sort the sub-arrays
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

//Convert Decimal into Binary 
vector<string> decToBin(vector<double> vec){
    vector<string>  result;
    cout<<"Binary representation: "<< endl;
    for(int i = 0; i<vec.size(); i++){

        //Before the comme
        double decNum = vec[i];
        int intPart = (int) decNum;
        bitset<32> binary_int(intPart);

        //After the comma
        double dec = decNum - intPart;
        string binary_dec = ".";

    for (int i = 0; i < NUMBEROFBITS; ++i) {
        dec *= 2;
        int bit = static_cast<int>(dec);
        binary_dec += to_string(bit);
        dec -= bit;
    }
        result.push_back( binary_int.to_string() + binary_dec);
        cout<< result[i] << endl ;
    }
    return result;
}

 int main(){
 vector<double> numbers;

    // Input from the user
    cout << "Enter decimal numbers. Enter a non-numeric value to stop.\n";

    double num;
    while (cin >> num) {
        numbers.push_back(num);
    }
    PRINT("-------------------");
    SHOW(numbers);
    PRINT("-------------------");
    QUICKSORT(numbers);
    SHOW(numbers);
    PRINT("-------------------");
    vector<string> result = decToBin(numbers);
    PRINT("-------------------");

    return 0;
}