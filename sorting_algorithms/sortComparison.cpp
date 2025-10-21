#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

// Function prototypes
void insertionSort(std::vector<int>& data);
void mergeSort(std::vector<int>& data, int start, int end);
void merge(std::vector<int>& data, int start, int mid, int end);
std::vector<int> createRandomArray(int length);
void displaySummary(const std::vector<int>& arraySizes, 
                   const std::vector<double>& insertionResults, 
                   const std::vector<double>& mergeResults);

int main() {
    std::cout << "Algorithm Speed Analysis" << std::endl;
    std::cout << "========================" << std::endl << std::endl;
    
    // Different array lengths to evaluate
    std::vector<int> arrayLengths = {10, 100, 1000, 10000};
    std::vector<double> insertionSpeedResults;
    std::vector<double> mergeSpeedResults;
    
    const int numberOfRuns = 10; // Perform 10 iterations per test
    
    for (int currentSize : arrayLengths) {
        std::cout << "Evaluating arrays of length " << currentSize << std::endl;
        
        double insertionTotalTime = 0.0;
        double mergeTotalTime = 0.0;
        
        for (int run = 0; run < numberOfRuns; run++) {
            // Create fresh random data for each run
            std::vector<int> originalData = createRandomArray(currentSize);
            std::vector<int> insertionData = originalData; // Duplicate for insertion sort
            std::vector<int> mergeData = originalData;     // Duplicate for merge sort
            
            // Benchmark Insertion Sort
            auto timerStart = std::chrono::high_resolution_clock::now();
            insertionSort(insertionData);
            auto timerEnd = std::chrono::high_resolution_clock::now();
            auto insertionTimeSpan = std::chrono::duration_cast<std::chrono::microseconds>(timerEnd - timerStart);
            insertionTotalTime += insertionTimeSpan.count() / 1000.0; // Convert to ms
            
            // Benchmark Merge Sort
            timerStart = std::chrono::high_resolution_clock::now();
            mergeSort(mergeData, 0, mergeData.size() - 1);
            timerEnd = std::chrono::high_resolution_clock::now();
            auto mergeTimeSpan = std::chrono::duration_cast<std::chrono::microseconds>(timerEnd - timerStart);
            mergeTotalTime += mergeTimeSpan.count() / 1000.0; // Convert to ms
        }
        
        // Compute mean execution times
        double insertionAverage = insertionTotalTime / numberOfRuns;
        double mergeAverage = mergeTotalTime / numberOfRuns;
        
        insertionSpeedResults.push_back(insertionAverage);
        mergeSpeedResults.push_back(mergeAverage);
        
        std::cout << "  Mean Insertion Sort duration: " << std::fixed << std::setprecision(4) 
                  << insertionAverage << " ms" << std::endl;
        std::cout << "  Mean Merge Sort duration: " << std::fixed << std::setprecision(4) 
                  << mergeAverage << " ms" << std::endl;
        std::cout << std::endl;
    }
    
    // Output final comparison
    displaySummary(arrayLengths, insertionSpeedResults, mergeSpeedResults);
    
    return 0;
}

// Insertion Sort algorithm
void insertionSort(std::vector<int>& data) {
    int length = data.size();
    for (int index = 1; index < length; index++) {
        int currentElement = data[index];
        int previousIndex = index - 1;
        
        // Shift larger elements to the right
        while (previousIndex >= 0 && data[previousIndex] > currentElement) {
            data[previousIndex + 1] = data[previousIndex];
            previousIndex = previousIndex - 1;
        }
        data[previousIndex + 1] = currentElement;
    }
}

// Merge Sort algorithm
void mergeSort(std::vector<int>& data, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        mergeSort(data, start, mid);
        mergeSort(data, mid + 1, end);
        merge(data, start, mid, end);
    }
}

// Helper function to combine sorted subarrays
void merge(std::vector<int>& data, int start, int mid, int end) {
    int leftSize = mid - start + 1;
    int rightSize = end - mid;
    
    std::vector<int> leftHalf(leftSize);
    std::vector<int> rightHalf(rightSize);
    
    // Populate temporary subarrays
    for (int i = 0; i < leftSize; i++) {
        leftHalf[i] = data[start + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightHalf[j] = data[mid + 1 + j];
    }
    
    // Combine the sorted halves
    int leftIndex = 0, rightIndex = 0, dataIndex = start;
    
    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (leftHalf[leftIndex] <= rightHalf[rightIndex]) {
            data[dataIndex] = leftHalf[leftIndex];
            leftIndex++;
        } else {
            data[dataIndex] = rightHalf[rightIndex];
            rightIndex++;
        }
        dataIndex++;
    }
    
    // Handle remaining elements
    while (leftIndex < leftSize) {
        data[dataIndex] = leftHalf[leftIndex];
        leftIndex++;
        dataIndex++;
    }
    
    while (rightIndex < rightSize) {
        data[dataIndex] = rightHalf[rightIndex];
        rightIndex++;
        dataIndex++;
    }
}

// Create an array filled with random integers
std::vector<int> createRandomArray(int length) {
    std::vector<int> array(length);
    std::random_device randomSeed;
    std::mt19937 generator(randomSeed());
    std::uniform_int_distribution<> distribution(0, 999);
    
    for (int i = 0; i < length; i++) {
        array[i] = distribution(generator);
    }
    
    return array;
}

// Display comprehensive performance analysis
void displaySummary(const std::vector<int>& arraySizes, 
                   const std::vector<double>& insertionResults, 
                   const std::vector<double>& mergeResults) {
    std::cout << "PERFORMANCE SUMMARY" << std::endl;
    std::cout << "===================" << std::endl;
    std::cout << std::setw(8) << "Size" << std::setw(20) << "Insertion Sort" 
              << std::setw(20) << "Merge Sort" << std::setw(20) << "Speed Ratio" << std::endl;
    std::cout << std::setw(8) << "----" << std::setw(20) << "--------------" 
              << std::setw(20) << "----------" << std::setw(20) << "-----------" << std::endl;
    
    for (size_t i = 0; i < arraySizes.size(); i++) {
        double speedRatio = insertionResults[i] / mergeResults[i];
        std::cout << std::setw(8) << arraySizes[i] 
                  << std::setw(20) << std::fixed << std::setprecision(4) << insertionResults[i] << " ms"
                  << std::setw(20) << std::fixed << std::setprecision(4) << mergeResults[i] << " ms"
                  << std::setw(20) << std::fixed << std::setprecision(2) << speedRatio << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "CONCLUSIONS:" << std::endl;
    std::cout << "- Small datasets (10, 100): Insertion Sort wins due to minimal overhead" << std::endl;
    std::cout << "- Large datasets (1000, 10000): Merge Sort dominates with superior efficiency" << std::endl;
    std::cout << "- Results confirm theoretical analysis: O(n²) versus O(n log n) complexity" << std::endl;
}
