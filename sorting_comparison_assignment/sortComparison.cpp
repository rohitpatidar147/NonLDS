#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>

// Helper function for radix sort - gets the length of a number in digits
int radixGetLength(int value) {
    if (value == 0) return 1;
    int digits = 0;
    while (value != 0) {
        digits++;
        value = value / 10;
    }
    return digits;
}

// Helper function for radix sort - gets the maximum length in digits
int radixGetMaxLength(const std::vector<int>& array) {
    int maxDigits = 0;
    for (int i = 0; i < array.size(); i++) {
        int digitCount = radixGetLength(array[i]);
        if (digitCount > maxDigits) {
            maxDigits = digitCount;
        }
    }
    return maxDigits;
}

// a) Insertion Sort function from homework 5
void insertionSort(std::vector<int>& numbers) {
    for (int i = 1; i < numbers.size(); i++) {
        int key = numbers[i];
        int j = i - 1;
        
        // Move elements that are greater than key one position ahead
        while (j >= 0 && numbers[j] > key) {
            numbers[j + 1] = numbers[j];
            j = j - 1;
        }
        numbers[j + 1] = key;
    }
}

// b) Bucket Sort function
void bucketSort(std::vector<int>& numbers, int numBuckets) {
    if (numbers.size() < 1) return;
    
    // Create buckets
    std::vector<std::vector<int>> buckets(numBuckets);
    
    // Find the maximum value
    int maxValue = numbers[0];
    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] > maxValue) {
            maxValue = numbers[i];
        }
    }
    
    // Put each number in a bucket
    for (int number : numbers) {
        int index = (number * numBuckets) / (maxValue + 1);
        buckets[index].push_back(number);
    }
    
    // Sort each bucket using insertion sort
    for (auto& bucket : buckets) {
        insertionSort(bucket);
    }
    
    // Combine all buckets back into numbers list
    int index = 0;
    for (const auto& bucket : buckets) {
        for (int value : bucket) {
            numbers[index++] = value;
        }
    }
}

// c) Radix Sort function
void radixSort(std::vector<int>& numbers) {
    if (numbers.empty()) return;
    
    std::vector<std::vector<int>> buckets(10);
    
    // Find the max length, in number of digits
    int maxDigits = radixGetMaxLength(numbers);
    
    // Start with the least significant digit
    int pow10 = 1;
    for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
        for (int i = 0; i < numbers.size(); i++) {
            int bucketIndex = (numbers[i] / pow10) % 10;
            buckets[bucketIndex].push_back(numbers[i]);
        }
        
        int arrayIndex = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < buckets[i].size(); j++) {
                numbers[arrayIndex++] = buckets[i][j];
            }
        }
        
        pow10 = 10 * pow10;
        
        // Clear all buckets
        for (auto& bucket : buckets) {
            bucket.clear();
        }
    }
}

// Function to generate random vector of given size with values 0-999
std::vector<int> generateRandomVector(int size) {
    std::vector<int> numbers(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 999);
    
    for (int i = 0; i < size; i++) {
        numbers[i] = dis(gen);
    }
    
    return numbers;
}

// Function to copy a vector
std::vector<int> copyVector(const std::vector<int>& original) {
    return std::vector<int>(original);
}

// Function to test a sorting algorithm and return time in milliseconds
double testSortingAlgorithm(void (*sortFunc)(std::vector<int>&), std::vector<int> numbers) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(numbers);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return duration.count() / 1000.0; // Convert to milliseconds
}

// Function to test bucket sort with specific number of buckets
double testBucketSort(std::vector<int> numbers, int numBuckets) {
    auto start = std::chrono::high_resolution_clock::now();
    bucketSort(numbers, numBuckets);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return duration.count() / 1000.0; // Convert to milliseconds
}

int main() {
    std::cout << "Sorting Algorithm Comparison\n";
    std::cout << "============================\n\n";
    
    // Test sizes
    std::vector<int> testSizes = {10, 100, 1000, 10000};
    int numIterations = 10;
    
    // Results storage
    std::vector<std::vector<double>> insertionTimes(testSizes.size());
    std::vector<std::vector<double>> bucketTimes(testSizes.size());
    std::vector<std::vector<double>> radixTimes(testSizes.size());
    
    // Run tests for each size
    for (int sizeIndex = 0; sizeIndex < testSizes.size(); sizeIndex++) {
        int size = testSizes[sizeIndex];
        std::cout << "Testing with size " << size << ":\n";
        
        for (int iter = 0; iter < numIterations; iter++) {
            // Generate random vector
            std::vector<int> originalNumbers = generateRandomVector(size);
            
            // Test Insertion Sort
            std::vector<int> numbers1 = copyVector(originalNumbers);
            double insertionTime = testSortingAlgorithm(insertionSort, numbers1);
            insertionTimes[sizeIndex].push_back(insertionTime);
            
            // Test Bucket Sort (using size/10 buckets)
            std::vector<int> numbers2 = copyVector(originalNumbers);
            double bucketTime = testBucketSort(numbers2, size / 10);
            bucketTimes[sizeIndex].push_back(bucketTime);
            
            // Test Radix Sort
            std::vector<int> numbers3 = copyVector(originalNumbers);
            double radixTime = testSortingAlgorithm(radixSort, numbers3);
            radixTimes[sizeIndex].push_back(radixTime);
        }
        
        std::cout << "Completed " << numIterations << " iterations for size " << size << "\n\n";
    }
    
    // Calculate and display averages
    std::cout << "RESULTS (Average wall clock times in milliseconds):\n";
    std::cout << "==================================================\n";
    std::cout << std::left << std::setw(10) << "Size" 
              << std::setw(20) << "Insertion Sort" 
              << std::setw(20) << "Bucket Sort" 
              << std::setw(15) << "Radix Sort" << "\n";
    std::cout << "-----------------------------------------------------------\n";
    
    for (int sizeIndex = 0; sizeIndex < testSizes.size(); sizeIndex++) {
        int size = testSizes[sizeIndex];
        
        // Calculate averages
        double avgInsertion = 0, avgBucket = 0, avgRadix = 0;
        for (int i = 0; i < numIterations; i++) {
            avgInsertion += insertionTimes[sizeIndex][i];
            avgBucket += bucketTimes[sizeIndex][i];
            avgRadix += radixTimes[sizeIndex][i];
        }
        avgInsertion /= numIterations;
        avgBucket /= numIterations;
        avgRadix /= numIterations;
        
        std::cout << std::left << std::setw(10) << size
                  << std::setw(20) << std::fixed << std::setprecision(4) << avgInsertion
                  << std::setw(20) << std::fixed << std::setprecision(4) << avgBucket
                  << std::setw(15) << std::fixed << std::setprecision(4) << avgRadix << "\n";
    }
    
    std::cout << "\nDetailed Results for Analysis:\n";
    std::cout << "==============================\n";
    
    for (int sizeIndex = 0; sizeIndex < testSizes.size(); sizeIndex++) {
        int size = testSizes[sizeIndex];
        std::cout << "\nSize " << size << ":\n";
        std::cout << "Insertion Sort times: ";
        for (double time : insertionTimes[sizeIndex]) {
            std::cout << std::fixed << std::setprecision(4) << time << " ";
        }
        std::cout << "\nBucket Sort times: ";
        for (double time : bucketTimes[sizeIndex]) {
            std::cout << std::fixed << std::setprecision(4) << time << " ";
        }
        std::cout << "\nRadix Sort times: ";
        for (double time : radixTimes[sizeIndex]) {
            std::cout << std::fixed << std::setprecision(4) << time << " ";
        }
        std::cout << "\n";
    }
    
    return 0;
}
