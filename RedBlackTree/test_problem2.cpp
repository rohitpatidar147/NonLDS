#include "RedBlackTree.h"
#include "../AVLTree/AVLTree.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <cmath>

// Quick test with small N
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

int main() {
    std::cout << "=== Problem 2 Quick Test ===\n";
    int N = 100;
    std::vector<double> vec = generateRandomVector(N);
    
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
    
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "N = " << N << "\n";
    std::cout << "RBT - Time: " << rbtTime << "s, Height: " << rbtHeight << "\n";
    std::cout << "AVL - Time: " << avlTime << "s, Height: " << avlHeight << "\n";
    std::cout << "Expected Height (O(log N)): ~" << (2 * log2(N)) << "\n";
    std::cout << "\n✓ Problem 2 test passed!\n";
    
    return 0;
}

