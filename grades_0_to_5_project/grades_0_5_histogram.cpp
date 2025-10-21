#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> grades;
    int grade;

    cout << "Enter grades between 0 and 5 (enter -1 to stop):\n";

    while (true) {
        if (!(cin >> grade)) {
            cin.clear();
            string skip;
            getline(cin, skip);
            cout << "Invalid input. Please enter an integer between 0 and 5, or -1 to stop." << endl;
            continue;
        }
        if (grade == -1) break; // stop input
        if (grade >= 0 && grade <= 5) {
            grades.push_back(grade);
        } else {
            cout << "Invalid grade. Please enter between 0 and 5." << endl;
        }
    }

    // histogram array
    int counts[6] = {0};
    for (int g : grades) {
        counts[g]++;
    }

    // Print histogram
    for (int i = 0; i < 6; i++) {
        cout << counts[i] << " grade(s) of " << i << endl;
    }

    return 0;
}
