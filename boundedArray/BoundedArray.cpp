#include <string>
#include <stdexcept>
#include "BoundedArray.h"

BoundedArray::BoundedArray() {
	maxCapacity = 100; // Standard capacity setting
	currentSize = 0;
	storage = new double[maxCapacity];
	for (int i = 0; i < maxCapacity; i++)
		storage[i] = 0;
}

BoundedArray::BoundedArray(int initialSize) {
	maxCapacity = 100; // Standard capacity setting
	currentSize = 0;
	storage = new double[maxCapacity];
	for (int i = 0; i < maxCapacity; i++)
		storage[i] = 0;
	resize(initialSize);
}

BoundedArray::BoundedArray(int initialSize, int maxCapacity) {
	if (maxCapacity <= 0)
		throw std::out_of_range("Invalid maximum capacity " + std::to_string(maxCapacity));
	if (initialSize > maxCapacity || initialSize < 0)
		throw std::out_of_range("Invalid size " + std::to_string(initialSize));
	
	this->maxCapacity = maxCapacity;
	currentSize = initialSize;
	storage = new double[maxCapacity];
	for (int i = 0; i < maxCapacity; i++)
		storage[i] = 0;
}

BoundedArray::BoundedArray(BoundedArray& source) {
	maxCapacity = source.capacity();
	currentSize = source.size();
	storage = new double[maxCapacity];
	for (int i = 0; i < maxCapacity; i++)
		storage[i] = 0;
	operator=(source);
}

BoundedArray::~BoundedArray() {
	delete[] storage;
}

int BoundedArray::size() {
	return currentSize;
}

int BoundedArray::capacity() {
	return maxCapacity;
}

double& BoundedArray::operator[](int position) {
	return storage[position];
}

double& BoundedArray::at(int position) {
	if (position >= currentSize || position < 0)
		throw std::out_of_range("Invalid index " + std::to_string(position));
	return operator[](position);
}

double* BoundedArray::data() {
	return storage;
}

BoundedArray& BoundedArray::operator=(BoundedArray& source) {
	// Reallocate memory if capacity differs
	if (maxCapacity != source.capacity()) {
		delete[] storage;
		maxCapacity = source.capacity();
		storage = new double[maxCapacity];
	}
	
	currentSize = source.size();
	for (int i = 0; i < currentSize; i++)
		storage[i] = source[i];
	for (int i = currentSize; i < maxCapacity; i++)
		storage[i] = 0;

	return *this;
}

void BoundedArray::resize(int targetSize) {
	if (targetSize > maxCapacity || targetSize < 0)
		throw std::out_of_range("Invalid size " + std::to_string(targetSize));
	currentSize = targetSize;
}

void BoundedArray::push_back(double newValue) {
	if (currentSize >= maxCapacity)
		throw std::out_of_range("Array has reached its maximum capacity");

	storage[currentSize] = newValue;
	currentSize++;
}

void BoundedArray::pop_back() {
	if (currentSize == 0)
		throw std::out_of_range("Array has no elements");

	currentSize--;
	storage[currentSize] = 0;
}

void BoundedArray::insert(int position, double newValue) {
	if (position > currentSize || position < 0)
		throw std::out_of_range("Invalid index " + std::to_string(position));
	if (currentSize >= maxCapacity)
		throw std::out_of_range("Array has reached its maximum capacity");

	for (int i = currentSize; i > position; i--)
		storage[i] = storage[i - 1];
	storage[position] = newValue;
	currentSize++;
}

void BoundedArray::erase(int position) {
	if (position >= currentSize || position < 0)
		throw std::out_of_range("Invalid index " + std::to_string(position));
	
	for (int i = position; i < currentSize - 1; i++)
		storage[i] = storage[i + 1];
	currentSize--;
	storage[currentSize] = 0;
}

void BoundedArray::clear() {
	for (int i = 0; i < currentSize; i++)
		storage[i] = 0;
	currentSize = 0;
}
