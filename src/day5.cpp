#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

bool is_valid_order(std::unordered_map<int, std::unordered_set<int>>& rules, std::vector<int>& update) {
    // iterate through update vector, checking rules
    for (size_t i = 0; i < update.size(); ++i) {
        for (size_t j = i + 1; j < update.size(); ++j) {
            if (rules.at(update[j]).count(update[i])) {
                return false;
            }
        }
    }
    return true;
}

int fix_order(std::unordered_map<int, std::unordered_set<int>>& rules, std::vector<int>& update) {
    // while update is NOT in a valid order, iterate through vector swapping indices that violate rules
    do {
        for (size_t i = 0; i < update.size(); ++i) {
            for (size_t j = i + 1; j < update.size(); ++j) {
                if (rules.at(update[j]).count(update[i])) {
                    int temp = update[i];
                    update[i] = update[j];
                    update[j] = temp;
                }
            }
        }
    } while (!is_valid_order(rules, update));

    int middleIndex = update.size() / 2;
    return update[middleIndex];
}

int main() {
    // Open input from file
    std::string filename = "../inputs/day5.txt";
    std::unordered_map<int, std::unordered_set<int>> rules;
    std::vector<std::vector<int>> updates;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    bool parse_rules = true;
    std::string line;
    while (std::getline(file, line)) {
        // Break if empty line is encountered
        if (line.empty()) {
            parse_rules = false;
        }

        if (parse_rules) {
            // parse first portion of input
            std::istringstream iss(line);
            int first, second;
            char delimiter;
            
            if (iss >> first >> delimiter >> second) {
                rules[first].insert(second);
                if (rules.find(second) == rules.end()) {
                    rules[second] = {};
                }
            } else {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        } else {
            // parse second portion of input
            std::vector<int> update;
            std::istringstream iss(line);
            int page;
            while (iss >> page) {
                update.push_back(page);
                if (iss.peek() == ',') iss.ignore();
            }

            if (!update.empty()) {
                updates.push_back(update);
            }
        }
    }

    // solve
    int acc1 = 0;
    int acc2 = 0;
    for (std::vector<int> update : updates) {
        if (is_valid_order(rules, update)) {
            int middleIndex = update.size() / 2;
            acc1 += update[middleIndex];
        } else {
            acc2 += fix_order(rules, update);
        }
    }

    std::cout << "Part 1: " << acc1 << std::endl;
    std::cout << "Part 2: " << acc2 << std::endl;

    return 0;
}