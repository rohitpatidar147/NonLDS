#include "RedBlackTree.h"
#include "../AVLTree/AVLTree.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <cmath>

// Generate a random vector of N doubles in [0, 1]
std::vector<double> generateRandomVector(int N) {
    std::vector<double> vec(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    
    for (int i = 0; i < N; i++) {
        vec[i] = dis(gen);
    }
    return vec;
}

// Generate a sorted vector of N doubles in [0, 1]
std::vector<double> generateSortedVector(int N) {
    std::vector<double> vec = generateRandomVector(N);
    std::sort(vec.begin(), vec.end());
    return vec;
}

// Generate a partially sorted vector: first 25% random, middle 50% sorted, last 25% random
std::vector<double> generatePartiallySortedVector(int N) {
    std::vector<double> vec = generateRandomVector(N);
    
    // Sort the middle 50% (from index N/4 to 3N/4)
    int start = N / 4;
    int end = 3 * N / 4;
    std::sort(vec.begin() + start, vec.begin() + end);
    
    return vec;
}

int main() {
    std::vector<int> sizes = {100, 1000, 10000, 100000};
    int numTrials = 10;
    
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "AVL vs Red-Black Tree Comparison\n";
    std::cout << "=================================\n\n";
    
    for (int N : sizes) {
        std::cout << "N = " << N << "\n";
        std::cout << "----------------------------------------\n";
        
        // Test Random Vectors
        {
            double totalRBTTime = 0.0;
            double totalAVLTime = 0.0;
            int totalRBTHeight = 0;
            int totalAVLHeight = 0;
            
            for (int trial = 0; trial < numTrials; trial++) {
                std::vector<double> vec = generateRandomVector(N);
                
                // Test Red-Black Tree
                RedBlackTree rbt;
                auto start = std::chrono::high_resolution_clock::now();
                for (double val : vec) {
                    rbt.insert(new RBTNode(val));
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double rbtTime = duration.count() / 1000000.0; // Convert to seconds
                int rbtHeight = rbt.getHeight();
                
                totalRBTTime += rbtTime;
                totalRBTHeight += rbtHeight;
                
                // Test AVL Tree
                AVLTree avl;
                start = std::chrono::high_resolution_clock::now();
                for (double val : vec) {
                    avl.insert(new Node(val));
                }
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double avlTime = duration.count() / 1000000.0; // Convert to seconds
                int avlHeight = avl.getHeight();
                
                totalAVLTime += avlTime;
                totalAVLHeight += avlHeight;
            }
            
            double avgRBTTime = totalRBTTime / numTrials;
            double avgAVLTime = totalAVLTime / numTrials;
            double avgRBTHeight = totalRBTHeight / (double)numTrials;
            double avgAVLHeight = totalAVLHeight / (double)numTrials;
            
            std::cout << "Random Vectors:\n";
            std::cout << "  RBT - Avg Time: " << avgRBTTime << "s, Avg Height: " << avgRBTHeight << "\n";
            std::cout << "  AVL - Avg Time: " << avgAVLTime << "s, Avg Height: " << avgAVLHeight << "\n";
            std::cout << "  Expected Height (O(log N)): ~" << (2 * log2(N)) << "\n\n";
        }
        
        // Test Sorted Vectors
        {
            double totalRBTTime = 0.0;
            double totalAVLTime = 0.0;
            int totalRBTHeight = 0;
            int totalAVLHeight = 0;
            
            for (int trial = 0; trial < numTrials; trial++) {
                std::vector<double> vec = generateSortedVector(N);
                
                // Test Red-Black Tree
                RedBlackTree rbt;
                auto start = std::chrono::high_resolution_clock::now();
                for (double val : vec) {
                    rbt.insert(new RBTNode(val));
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double rbtTime = duration.count() / 1000000.0;
                int rbtHeight = rbt.getHeight();
                
                totalRBTTime += rbtTime;
                totalRBTHeight += rbtHeight;
                
                // Test AVL Tree
                AVLTree avl;
                start = std::chrono::high_resolution_clock::now();
                for (double val : vec) {
                    avl.insert(new Node(val));
                }
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double avlTime = duration.count() / 1000000.0;
                int avlHeight = avl.getHeight();
                
                totalAVLTime += avlTime;
                totalAVLHeight += avlHeight;
            }
            
            double avgRBTTime = totalRBTTime / numTrials;
            double avgAVLTime = totalAVLTime / numTrials;
            double avgRBTHeight = totalRBTHeight / (double)numTrials;
            double avgAVLHeight = totalAVLHeight / (double)numTrials;
            
            std::cout << "Sorted Vectors:\n";
            std::cout << "  RBT - Avg Time: " << avgRBTTime << "s, Avg Height: " << avgRBTHeight << "\n";
            std::cout << "  AVL - Avg Time: " << avgAVLTime << "s, Avg Height: " << avgAVLHeight << "\n";
            std::cout << "  Expected Height (O(log N)): ~" << (2 * log2(N)) << "\n\n";
        }
        
        // Test Partially Sorted Vectors
        {
            double totalRBTTime = 0.0;
            double totalAVLTime = 0.0;
            int totalRBTHeight = 0;
            int totalAVLHeight = 0;
            
            for (int trial = 0; trial < numTrials; trial++) {
                std::vector<double> vec = generatePartiallySortedVector(N);
                
                // Test Red-Black Tree
                RedBlackTree rbt;
                auto start = std::chrono::high_resolution_clock::now();
                for (double val : vec) {
                    rbt.insert(new RBTNode(val));
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double rbtTime = duration.count() / 1000000.0;
                int rbtHeight = rbt.getHeight();
                
                totalRBTTime += rbtTime;
                totalRBTHeight += rbtHeight;
                
                // Test AVL Tree
                AVLTree avl;
                start = std::chrono::high_resolution_clock::now();
                for (double val : vec) {
                    avl.insert(new Node(val));
                }
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double avlTime = duration.count() / 1000000.0;
                int avlHeight = avl.getHeight();
                
                totalAVLTime += avlTime;
                totalAVLHeight += avlHeight;
            }
            
            double avgRBTTime = totalRBTTime / numTrials;
            double avgAVLTime = totalAVLTime / numTrials;
            double avgRBTHeight = totalRBTHeight / (double)numTrials;
            double avgAVLHeight = totalAVLHeight / (double)numTrials;
            
            std::cout << "Partially Sorted Vectors:\n";
            std::cout << "  RBT - Avg Time: " << avgRBTTime << "s, Avg Height: " << avgRBTHeight << "\n";
            std::cout << "  AVL - Avg Time: " << avgAVLTime << "s, Avg Height: " << avgAVLHeight << "\n";
            std::cout << "  Expected Height (O(log N)): ~" << (2 * log2(N)) << "\n\n";
        }
        
        std::cout << "\n";
    }
    
    return 0;
}

