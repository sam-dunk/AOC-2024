#include <iostream>
#include <fstream>
#include <sstream>  
#include <string>
#include <vector>
#include <cmath>


bool test_safe(std::vector<int>& report) {
    int prev;
    int number;
    bool inc = false;

    for (std::size_t i = 1; i < report.size(); ++i) {
        if (i == 1) {
            prev = report[i-1];
            number = report[i];
            if (prev < number) {
                inc = true;
            }
        } else {
            number = report[i];
            if ((inc && prev > number) || (!inc && prev < number)) {
                return false;
            }
        }
        int diff = abs(prev - number);
        if (diff < 1 || diff > 3) {
            return false;
        }
        prev = number;
    }

    return true;
}

bool test_safe_dampened(std::vector<int>& report) {
    // the longest report is like 8 levels long - were just gonna brute force it
    for (std::size_t i = 0; i < report.size(); ++i) {
        std::vector<int> damp = report;
        damp.erase(damp.begin() + i);
        if (test_safe(damp)) {
            return true;
        }
    }
    return false;
}


int main () {
    // get data from input file
    std::ifstream input ("../inputs/day2.txt");
    std::vector<std::vector<int>> reports;
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {
            std::vector<int> levels;
            std::istringstream lstream(line);
            int number;
            while (lstream >> number) {
                levels.push_back(number);
            }
            reports.push_back(levels);
        }
    }
    input.close();

    // compute number of safe reports
    int num_safe = 0;
    int num_safe_dampened = 0;
    for (std::vector<int>&report : reports) {
        if (test_safe(report)) {
            ++num_safe;
            ++num_safe_dampened;
        } else if (test_safe_dampened(report)) {
            ++num_safe_dampened;
        }
    }

    // output result;
    std::cout << "Number safe (P1): " << num_safe << std::endl;
    std::cout << "Number safe (P2): " << num_safe_dampened << std::endl;

    exit(0);
}