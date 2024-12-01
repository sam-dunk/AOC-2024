#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

void list_difference(std::vector<int> &list1, std::vector<int> &list2) {
    int acc = 0;
    for (std::size_t i = 0; i < list1.size(); ++i) {
        acc += abs(list1[i] - list2[i]);
    }
    std::cout << "Difference: " << acc << std::endl;
}

void list_similarity(std::vector<int> &list1, std::vector<int> &list2) {
    std::map<int, int> freq;
    for (int id : list2) {
        ++freq[id];
    }

    int acc = 0;
    for (int id : list1) {
        acc += id * freq[id];
    }
    std::cout << "Similarity: " << acc << std::endl;
}

int main() {
    std::ifstream input ("../inputs/day1.txt");
    if (input.is_open()) {
        std::vector<int> list1;
        std::vector<int> list2;

        int id1, id2;
        while (input >> id1 >> id2) {
            list1.push_back(id1);
            list2.push_back(id2);
        }

        std::sort(list1.begin(), list1.end());
        std::sort(list2.begin(), list2.end());

        list_difference(list1, list2);
        list_similarity(list1, list2);

        input.close();
    } else {
        std::cerr << "unable to open file" << std::endl;
    }

    exit(0);
}