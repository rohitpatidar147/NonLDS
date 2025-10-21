#include <iostream>
#include <array>
#include <string>
#include <sstream>

int main() {
    std::array<int, 6> counts{}; // initialized to zero

    std::cout << "Enter grades (0-5). Press Ctrl+D (Unix/macOS) or Ctrl+Z then Enter (Windows) when done:\n";

    int grade;
    while (std::cin >> grade) {
        if (grade < 0 || grade > 5) {
            std::cerr << "Warning: ignoring invalid grade '" << grade << "' (must be 0-5)\n";
            continue;
        }
        ++counts[grade];
    }

    std::cout << "\nHistogram:\n";
    for (int i = 0; i <= 5; ++i) {
        std::cout << counts[i] << " grade(s) of " << i << '\n';
    }

    return 0;
}
