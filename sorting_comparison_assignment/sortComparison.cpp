#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>

// Utility function to count digits in an integer for radix sorting
int countDigitLength(int num) {
    if (num == 0) return 1;
    int digitCount = 0;
    while (num != 0) {
        digitCount++;
        num = num / 10;
    }
    return digitCount;
}

// Utility function to find the maximum digit count in an array
int findMaxDigitCount(const std::vector<int>& data) {
    int maxDigitCount = 0;
    for (int i = 0; i < data.size(); i++) {
        int currentDigitCount = countDigitLength(data[i]);
        if (currentDigitCount > maxDigitCount) {
            maxDigitCount = currentDigitCount;
        }
    }
    return maxDigitCount;
}

// Implementation of insertion sort algorithm
void performInsertionSort(std::vector<int>& data) {
    for (int i = 1; i < data.size(); i++) {
        int currentElement = data[i];
        int previousIndex = i - 1;
        
        // Shift elements greater than current element to the right
        while (previousIndex >= 0 && data[previousIndex] > currentElement) {
            data[previousIndex + 1] = data[previousIndex];
            previousIndex = previousIndex - 1;
        }
        data[previousIndex + 1] = currentElement;
    }
}

// Implementation of bucket sort algorithm
void performBucketSort(std::vector<int>& data, int bucketCount) {
    if (data.size() < 1) return;
    
    // Initialize bucket containers
    std::vector<std::vector<int>> bucketList(bucketCount);
    
    // Determine the maximum value in the array
    int maximumValue = data[0];
    for (int i = 1; i < data.size(); i++) {
        if (data[i] > maximumValue) {
            maximumValue = data[i];
        }
    }
    
    // Distribute elements into appropriate buckets
    for (int element : data) {
        int bucketIndex = (element * bucketCount) / (maximumValue + 1);
        bucketList[bucketIndex].push_back(element);
    }
    
    // Sort each bucket individually using insertion sort
    for (auto& bucket : bucketList) {
        performInsertionSort(bucket);
    }
    
    // Merge all buckets back into the original array
    int currentIndex = 0;
    for (const auto& bucket : bucketList) {
        for (int value : bucket) {
            data[currentIndex++] = value;
        }
    }
}

// Implementation of radix sort algorithm
void performRadixSort(std::vector<int>& data) {
    if (data.empty()) return;
    
    std::vector<std::vector<int>> digitBuckets(10);
    
    // Calculate the maximum number of digits
    int maxDigitCount = findMaxDigitCount(data);
    
    // Process each digit position from least to most significant
    int powerOfTen = 1;
    for (int digitPosition = 0; digitPosition < maxDigitCount; digitPosition++) {
        for (int i = 0; i < data.size(); i++) {
            int bucketIndex = (data[i] / powerOfTen) % 10;
            digitBuckets[bucketIndex].push_back(data[i]);
        }
        
        int dataIndex = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < digitBuckets[i].size(); j++) {
                data[dataIndex++] = digitBuckets[i][j];
            }
        }
        
        powerOfTen = 10 * powerOfTen;
        
        // Reset all buckets for next iteration
        for (auto& bucket : digitBuckets) {
            bucket.clear();
        }
    }
}

// Function to create a random vector with specified size and range 0-999
std::vector<int> createRandomData(int dataSize) {
    std::vector<int> randomData(dataSize);
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(0, 999);
    
    for (int i = 0; i < dataSize; i++) {
        randomData[i] = distribution(generator);
    }
    
    return randomData;
}

// Function to duplicate a vector
std::vector<int> duplicateVector(const std::vector<int>& source) {
    return std::vector<int>(source);
}

// Function to measure sorting algorithm execution time in milliseconds
double measureSortingTime(void (*sortingFunction)(std::vector<int>&), std::vector<int> data) {
    auto startTime = std::chrono::high_resolution_clock::now();
    sortingFunction(data);
    auto endTime = std::chrono::high_resolution_clock::now();
    
    auto timeSpan = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return timeSpan.count() / 1000.0; // Convert to milliseconds
}

// Function to measure bucket sort execution time with specific bucket count
double measureBucketSortTime(std::vector<int> data, int bucketCount) {
    auto startTime = std::chrono::high_resolution_clock::now();
    performBucketSort(data, bucketCount);
    auto endTime = std::chrono::high_resolution_clock::now();
    
    auto timeSpan = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return timeSpan.count() / 1000.0; // Convert to milliseconds
}

int main() {
    std::cout << "Sorting Algorithm Comparison\n";
    std::cout << "============================\n\n";
    
    // Define test array sizes
    std::vector<int> arraySizes = {10, 100, 1000, 10000};
    int testRuns = 10;
    
    // Storage for timing results
    std::vector<std::vector<double>> insertionSortResults(arraySizes.size());
    std::vector<std::vector<double>> bucketSortResults(arraySizes.size());
    std::vector<std::vector<double>> radixSortResults(arraySizes.size());
    
    // Execute performance tests for each array size
    for (int sizeIndex = 0; sizeIndex < arraySizes.size(); sizeIndex++) {
        int currentSize = arraySizes[sizeIndex];
        std::cout << "Testing with size " << currentSize << ":\n";
        
        for (int run = 0; run < testRuns; run++) {
            // Create random test data
            std::vector<int> testData = createRandomData(currentSize);
            
            // Benchmark Insertion Sort
            std::vector<int> data1 = duplicateVector(testData);
            double insertionDuration = measureSortingTime(performInsertionSort, data1);
            insertionSortResults[sizeIndex].push_back(insertionDuration);
            
            // Benchmark Bucket Sort (using size/10 buckets)
            std::vector<int> data2 = duplicateVector(testData);
            double bucketDuration = measureBucketSortTime(data2, currentSize / 10);
            bucketSortResults[sizeIndex].push_back(bucketDuration);
            
            // Benchmark Radix Sort
            std::vector<int> data3 = duplicateVector(testData);
            double radixDuration = measureSortingTime(performRadixSort, data3);
            radixSortResults[sizeIndex].push_back(radixDuration);
        }
        
        std::cout << "Completed " << testRuns << " iterations for size " << currentSize << "\n\n";
    }
    
    // Compute and present average execution times
    std::cout << "RESULTS (Average wall clock times in milliseconds):\n";
    std::cout << "==================================================\n";
    std::cout << std::left << std::setw(10) << "Size" 
              << std::setw(20) << "Insertion Sort" 
              << std::setw(20) << "Bucket Sort" 
              << std::setw(15) << "Radix Sort" << "\n";
    std::cout << "-----------------------------------------------------------\n";
    
    for (int sizeIndex = 0; sizeIndex < arraySizes.size(); sizeIndex++) {
        int currentSize = arraySizes[sizeIndex];
        
        // Compute average execution times
        double avgInsertion = 0, avgBucket = 0, avgRadix = 0;
        for (int i = 0; i < testRuns; i++) {
            avgInsertion += insertionSortResults[sizeIndex][i];
            avgBucket += bucketSortResults[sizeIndex][i];
            avgRadix += radixSortResults[sizeIndex][i];
        }
        avgInsertion /= testRuns;
        avgBucket /= testRuns;
        avgRadix /= testRuns;
        
        std::cout << std::left << std::setw(10) << currentSize
                  << std::setw(20) << std::fixed << std::setprecision(4) << avgInsertion
                  << std::setw(20) << std::fixed << std::setprecision(4) << avgBucket
                  << std::setw(15) << std::fixed << std::setprecision(4) << avgRadix << "\n";
    }
    
    std::cout << "\nDetailed Results for Analysis:\n";
    std::cout << "==============================\n";
    
    for (int sizeIndex = 0; sizeIndex < arraySizes.size(); sizeIndex++) {
        int currentSize = arraySizes[sizeIndex];
        std::cout << "\nSize " << currentSize << ":\n";
        std::cout << "Insertion Sort times: ";
        for (double time : insertionSortResults[sizeIndex]) {
            std::cout << std::fixed << std::setprecision(4) << time << " ";
        }
        std::cout << "\nBucket Sort times: ";
        for (double time : bucketSortResults[sizeIndex]) {
            std::cout << std::fixed << std::setprecision(4) << time << " ";
        }
        std::cout << "\nRadix Sort times: ";
        for (double time : radixSortResults[sizeIndex]) {
            std::cout << std::fixed << std::setprecision(4) << time << " ";
        }
        std::cout << "\n";
    }
    
    return 0;
}
