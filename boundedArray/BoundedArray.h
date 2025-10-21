#ifndef BOUNDEDARRAY_H
#define BOUNDEDARRAY_H

class BoundedArray {
public:
	// Default constructor creates empty array with standard capacity
	BoundedArray();
	// Constructor creates array with initial size and standard capacity
	// Throws exception for invalid initial size
	BoundedArray(int initialSize);
	// Constructor creates array with specified size and custom capacity
	// Throws exception for invalid size or capacity parameters
	BoundedArray(int initialSize, int maxCapacity);
	// Copy constructor creates new array by duplicating existing array
	BoundedArray(BoundedArray& source);
	~BoundedArray();
	// Returns current number of elements stored in array
	int size();
	// Returns maximum number of elements array can hold
	int capacity();
	// Direct array access with no bounds checking
	double& operator[](int position);
	// Safe array access with bounds checking and exception throwing
	double& at(int position);
	// Returns raw pointer to underlying array storage
	double* data();
	// Assignment operator copies contents from another array
	BoundedArray& operator=(BoundedArray& source);
	// Modifies the logical size of the array
	void resize(int targetSize);
	// Appends new element to end of array
	// Throws exception if array is at maximum capacity
	void push_back(double newValue);
	// Removes last element from array
	// Throws exception if array is empty
	void pop_back();
	// Inserts new element at specified position, shifting others right
	// Throws exception for invalid position or full array
	void insert(int position, double newValue);
	// Removes element at specified position, shifting others left
	// Throws exception for invalid position
	void erase(int position);
	// Empties array by setting size to zero
	void clear();
private:
	// Upper limit on number of elements array can contain
	int maxCapacity;
	// Current count of elements in the array
	int currentSize;
	// Dynamically allocated storage for array elements
	double* storage;
};

#endif // !BOUNDEDARRAY_H
