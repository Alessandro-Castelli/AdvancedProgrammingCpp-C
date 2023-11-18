/* Create	a	simple	calculator	application	that	is	capable	to	add	and	multiply	up	to	four	operators	
using	only	variadic	macros.	Use	unique	identifiers	for	each	operation	to	invoke	the	correct	
macro	function.	 */

#include <iostream>
using namespace std;

#define SUM1(x) (x)
#define SUM2(x, y) (x + y)
#define SUM3(x, y, z) (x + y + z)
#define SUM4(x, y, z, w) (x + y + z + w)
#define GET_MACRO(a, b, c, d, NAME, ...) NAME
#define SUM(...) GET_MACRO(__VA_ARGS__, SUM4, SUM3, SUM2, SUM1)(__VA_ARGS__)

#define MUL1(x) (x)
#define MUL2(x, y) (x * y)
#define MUL3(x, y, z) (x * y * z)
#define MUL4(x, y, z, w) (x * y * z * w)
#define GET_MACRO2(a, b, c, d, NAME, ...) NAME
#define MUL(...) GET_MACRO2(__VA_ARGS__, MUL4, MUL3, MUL2, MUL1)(__VA_ARGS__)
int main() {
    cout << SUM(1) << endl; 
    cout << SUM(1, 2) << endl; 
    cout << SUM(1, 2, 3) << endl; 
    cout << SUM(1, 2, 3, 4) << endl; 

    cout << MUL(1) << endl; 
    cout << MUL(1, 2) << endl; 
    cout << MUL(1, 2, 3) << endl; 
    cout << MUL(1, 2, 3, 4) << endl; 

    return 0;
}
