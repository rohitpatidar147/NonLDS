#include "AVLTree.h"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

namespace {

struct Stats {
    int minimum;
    int maximum;
    double mean;
};

Stats summarize(const std::vector<int>& heights) {
    if (heights.empty())
        return { -1, -1, -1.0 };

    int low = heights.front();
    int high = heights.front();
    double total = 0.0;

    for (int h : heights) {
        low = std::min(low, h);
        high = std::max(high, h);
        total += static_cast<double>(h);
    }

    return { low, high, total / static_cast<double>(heights.size()) };
}

void displayStats(int n, const Stats& bstStats, const Stats& avlStats) {
    std::cout << "N = " << n << "\n";
    std::cout << "  BST (no rebalance):    min = " << bstStats.minimum
              << ", avg = " << std::fixed << std::setprecision(2) << bstStats.mean
              << ", max = " << bstStats.maximum << "\n";
    std::cout << "  AVL (balanced insert): min = " << avlStats.minimum
              << ", avg = " << std::fixed << std::setprecision(2) << avlStats.mean
              << ", max = " << avlStats.maximum << "\n";
    std::cout << "  Height reduction (avg): "
              << std::fixed << std::setprecision(2)
              << (bstStats.mean - avlStats.mean) << "\n\n";
}

} // namespace

int main() {
    std::vector<int> sizes = { 100, 1000, 10000, 100000 };
    const int trialsPerSize = 10;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int n : sizes) {
        std::vector<int> bstHeights;
        std::vector<int> avlHeights;
        bstHeights.reserve(trialsPerSize);
        avlHeights.reserve(trialsPerSize);

        for (int trial = 0; trial < trialsPerSize; ++trial) {
            AVLTree bst;
            AVLTree avl;

            for (int i = 0; i < n; ++i) {
                double value = distribution(rng);
                bst.insertWithoutRebalance(new Node(value));
                avl.insert(new Node(value));
            }

            bstHeights.push_back(bst.getHeight());
            avlHeights.push_back(avl.getHeight());
        }

        Stats bstStats = summarize(bstHeights);
        Stats avlStats = summarize(avlHeights);
        displayStats(n, bstStats, avlStats);
    }

    return 0;
}

