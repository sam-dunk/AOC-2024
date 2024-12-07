#include "../include/general.h"

std::vector<std::string>
gen_combinations_part1(int length)
{
    // returns a vector with every permutation of ops for Part 1
    std::vector<std::string> combinations;
    
    // Total number of combinations is 2^(length-1)
    // This is poopy but the vectors are short
    int ncomb = 1 << (length - 1);
    for (int i = 0; i < ncomb; ++i) {
        std::string ops;
        for (int j = 0; j < length - 1; ++j) {
            ops += (i & (1 << j)) ? '*' : '+';
        }
        combinations.push_back(ops);
    }

    return combinations;
}

std::vector<std::string>
gen_combinations_part2(int length)
{
    // returns a vector with every permutation of ops for Part 2
    std::vector<std::string> combinations;
    
    // Total number of combinations is 3^(length-1)
    int ncomb = pow(3, length - 1);
    for (int i = 0; i < ncomb; ++i) {
        std::string ops;
        int temp = i;
        for (int j = 0; j < length - 1; ++j) {
            int op = temp % 3;
            if (op == 0) {
                ops += '+';
            } else if (op == 1) {
                ops += '*';
            } else {
                ops += '|';
            }
            temp /= 3;
        }
        combinations.push_back(ops);
    }

    return combinations;
}

long long concatenate(long long a, long long b) {
    // Convert b to string to determine number of digits
    long long multiplier = 1;
    long long temp = b;
    while (temp > 0) {
        multiplier *= 10;
        temp /= 10;
    }
    
    return a * multiplier + b;
}

bool
test_eq_part1(std::pair<long long, std::vector<long long>>& eq)
{
    // test whether the equation can be satisfied with + and *
    long long target = eq.first;
    std::vector<long long> comp = eq.second;

    // generate permutation of ops
    std::vector<std::string> combs = gen_combinations_part1(comp.size());

    // see if any can satisfy eq
    for (std::string c : combs) {
        long long acc = comp[0];
        for (size_t i = 0; i < c.length(); ++i) {
            if (c[i] == '+') {
                acc += comp[i + 1];
            } else {
                acc *= comp[i + 1];
            }
        }
        if (acc == target) return true;
    }

    return false;
}

bool
test_eq_part2(std::pair<long long, std::vector<long long>>& eq)
{
    // test whether the equation can be satisfied with +, *, and ||
    long long target = eq.first;
    std::vector<long long> comp = eq.second;

    // generate permutation of ops
    std::vector<std::string> combs = gen_combinations_part2(comp.size());

    // see if any can satisfy eq
    for (const std::string& c : combs) {
        long long acc = comp[0];
        for (size_t i = 0; i < c.length(); ++i) {
            if (c[i] == '+') {
                acc += comp[i + 1];
            } else if (c[i] == '*') {
                acc *= comp[i + 1];
            } else {
                acc = concatenate(acc, comp[i + 1]);
            }
        }
        if (acc == target) return true;
    }

    return false;
}

int
main () 
{
    // Open input from file
    std::string filename = "../inputs/day7.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    // Parse inputs
    std::string line;
    std::vector<std::pair<long long, std::vector<long long>>> eqs;
    while (std::getline(file, line)) {
        size_t colon_pos = line.find(':');
        long long r = std::stoll(line.substr(0, colon_pos));
        std::istringstream lstream(line.substr(colon_pos + 1));
        std::vector<long long> v;
        long long number;
        while (lstream >> number) {
            v.push_back(number);
        }
        eqs.emplace_back(r, v);
    }

    // Part 1
    long long acc1 = 0;
    for (std::pair<long long, std::vector<long long>> eq : eqs) {
        if (test_eq_part1(eq)) acc1 += eq.first;
    }

    std::cout << "Part 1: " << acc1 << std::endl;

    // Part 2
    long long acc2 = 0;
    for (std::pair<long long, std::vector<long long>> eq : eqs) {
        if (test_eq_part2(eq)) acc2 += eq.first;
    }

    std::cout << "Part 2: " << acc2 << std::endl;

    return 0;
}