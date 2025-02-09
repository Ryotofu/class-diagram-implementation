#include <iostream>
#include <algorithm>
using namespace std;
const int SIZE = 10;
int main() {
int array1[SIZE], array2[SIZE], mergedArray[2 * SIZE];
int n1, n2;
cout << "Enter the number of elements (0-10) for array 1: ";
cin >> n1;
while (n1 < 0 || n1 > SIZE) {
cout << "Invalid input. Please enter a number between 0 and 10: ";
cin >> n1;
}
cout << "Enter the elements for array 1:\n";
for (int i = 0; i < n1; ++i) {
cin >> array1[i];
}
cout << "Enter the number of elements (0-10) for array 2: ";
cin >> n2;
while (n2 < 0 || n2 > SIZE) {
cout << "Invalid input. Please enter a number between 0 and 10: ";
cin >> n2;
}
cout << "Enter the elements for array 2:\n";
for (int i = 0; i < n2; ++i) {
cin >> array2[i];
}
int totalElements = n1 + n2;
for (int i = 0; i < n1; ++i) {
mergedArray[i] = array1[i];
}
for (int i = 0; i < n2; ++i) {
mergedArray[n1 + i] = array2[i];
}
sort(mergedArray, mergedArray + totalElements, greater<int>());
cout << "Merged array in descending order:\n";
for (int i = 0; i < totalElements; ++i) {
cout << mergedArray[i] << (i < totalElements - 1 ? " " : "");
}
cout << endl;
return 0;
}
