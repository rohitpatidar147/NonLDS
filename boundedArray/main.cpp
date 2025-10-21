// main.cpp : Test file for BoundedArray class
//

#include <iostream>
#include "BoundedArray.h"
using namespace std;

void printArray(BoundedArray& b) {
    for (int i = 0; i < b.size(); i++)
        cout << b.at(i) << " ";
    cout << endl;
}

void printArray(double* a, int numElements) {
    for (int i = 0; i < numElements; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main()
{
    cout << "=== Testing BoundedArray with Dynamic Capacity ===" << endl;
    
    // Test default constructor (capacity = 100)
    BoundedArray arr1, arr2, arr3;
    cout << "Default constructor - Capacity: " << arr1.capacity() << ", Size: " << arr1.size() << endl;
    
    // Test constructor with size (capacity = 100)
    BoundedArray arr4(5);
    cout << "Constructor with size 5 - Capacity: " << arr4.capacity() << ", Size: " << arr4.size() << endl;
    
    // Test constructor with size and capacity
    BoundedArray arr5(3, 10);
    cout << "Constructor with size 3, capacity 10 - Capacity: " << arr5.capacity() << ", Size: " << arr5.size() << endl;
    
    // Test push_back functionality
    arr1.push_back(0);
    arr1.push_back(4);
    arr2.push_back(1);
    arr2.push_back(6);
    cout << "Pushback, 0 4: ";
    printArray(arr1);
    cout << "1 6: ";
    printArray(arr2);
    
    // Test copy constructor
    BoundedArray arr6(arr2);
    cout << "Copy constructor - Capacity: " << arr6.capacity() << ", Size: " << arr6.size() << endl;
    cout << "1: " << arr6[0] << endl;
    cout << "6: " << arr6[1] << endl;
    
    // Test data() method
    double* arr1Elem = arr1.data();
    double* arr2Elem = arr2.data();
    double* arr6Elem = arr6.data();
    cout << "MemAddress arr2: " << arr2Elem << endl;
    cout << "MemAddress arr6: " << arr6Elem << endl;
    cout << "1 6: ";
    printArray(arr2Elem, arr2.size());
    cout << "1 6: ";
    printArray(arr6Elem, arr6.size());
    cout << "1 6: ";
    printArray(arr6);
    
    // Test insert functionality
    arr6.insert(1, 3);
    cout << "Insert at index 1, value 3: ";
    printArray(arr6);
    cout << "Original arr2 unchanged: ";
    printArray(arr2);
    
    // Test erase functionality
    arr6.erase(1);
    cout << "Erase index 1: ";
    printArray(arr6);
    cout << "Size after erase: " << arr6.size() << endl;
    
    // Test resize functionality
    arr6.resize(8);
    cout << "Size after resize to 8: " << arr6.size() << endl;
    
    // Test operator[] access
    cout << "arr1[1] = " << arr1[1] << endl;
    cout << "arr2[1] = " << arr2[1] << endl;
    cout << "arr1Elem[1] = " << arr1Elem[1] << endl;
    cout << "arr2Elem[1] = " << arr2Elem[1] << endl;
    
    // Test assignment operator
    arr2 = arr1;
    cout << "After assignment arr2 = arr1:" << endl;
    cout << "arr1[1] = " << arr1[1] << endl;
    cout << "arr2[1] = " << arr2[1] << endl;
    cout << "arr2Elem[1] = " << arr2Elem[1] << endl;
    
    // Test direct pointer modification
    arr2Elem[1] = -10;
    cout << "After arr2Elem[1] = -10: " << arr2Elem[1] << endl;
    
    // Test pop_back
    arr2.pop_back();
    cout << "After pop_back, accessing arr2.at(1): ";
    try {
        cout << arr2.at(1) << endl;
    } catch (const std::out_of_range& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
    // Test clear
    arr2.clear();
    cout << "After clear, accessing arr2.at(1): ";
    try {
        cout << arr2.at(1) << endl;
    } catch (const std::out_of_range& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
    // Test with different capacity
    arr3.resize(6);
    cout << "arr3 resized to 6 - Size: " << arr3.size() << endl;
    
    // Test assignment between arrays with different capacities
    BoundedArray arr7(2, 5);  // size 2, capacity 5
    BoundedArray arr8(3, 8);  // size 3, capacity 8
    arr7.push_back(1);
    arr7.push_back(2);
    arr8.push_back(10);
    arr8.push_back(20);
    arr8.push_back(30);
    
    cout << "Before assignment - arr7 capacity: " << arr7.capacity() << ", arr8 capacity: " << arr8.capacity() << endl;
    arr7 = arr8;  // This should change arr7's capacity to match arr8
    cout << "After assignment - arr7 capacity: " << arr7.capacity() << ", arr7 size: " << arr7.size() << endl;
    cout << "arr7 contents: ";
    printArray(arr7);
    
    cout << "\n=== All tests completed successfully! ===" << endl;
    return 0;
}