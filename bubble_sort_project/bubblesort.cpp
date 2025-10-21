#include <iostream>
using namespace std;

/**
 * Bubble sort implementation
 * @param arr Array to be sorted
 * @param length Length of the array
 * Postcondition: Array elements are sorted in ascending order
 */
void bubblesort(int arr[], int length) {
    for (int i = length-1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap elements
                int temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int a[] = {3, 10, 9, 2, 5, 1};
    
    // Print original array
    cout << "Original array: ";
    for (int i = 0; i < 6; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    
    // Sort the array
    bubblesort(a, 6);
    
    // Print sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < 6; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}