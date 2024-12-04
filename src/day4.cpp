#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <set>

class WordSearchSolver {
private:
    std::vector<std::vector<char>> grid;

    // Helper function to check if a word exists in a specific direction
    bool matchWord(const std::string& word, int startR, int startC, int dr, int dc, bool reverse = false) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Check boundary conditions
        if (startR + dr * (word.length()-1) < 0 || 
            startR + dr * (word.length()-1) >= rows ||
            startC + dc * (word.length()-1) < 0 || 
            startC + dc * (word.length()-1) >= cols) {
            return false;
        }
        
        // Check if word matches in this direction
        for (int i = 0; i < word.length(); i++) {
            char expected = reverse ? word[word.length() - 1 - i] : word[i];
            if (grid[startR + i*dr][startC + i*dc] != expected) {
                return false;
            }
        }
        return true;
    }

    // Helper function to check X-MAS pattern
    int checkXMASPattern(int r, int c) {
        // treat (r, c) as the center of the x-pattern. Need to check both diagonals
        std::vector<std::pair<int, int>> directions = {
            {1,1},    // Down-Right
            {1,-1},   // Down-Left
        };

        int xmasCount = 0;

        bool mas1_forward = matchWord("MAS", r-1, c-1, directions[0].first, directions[0].second);
        bool mas1_backward = matchWord("MAS", r-1, c-1, directions[0].first, directions[0].second, true);
        bool mas2_forward = matchWord("MAS", r-1, c+1, directions[1].first, directions[1].second);
        bool mas2_backward = matchWord("MAS", r-1, c+1, directions[1].first, directions[1].second, true);

        // if this is an x-pattern inc before returning value
        if ((mas1_forward || mas1_backward) && (mas2_forward || mas2_backward)) {
            ++xmasCount;
        }

        return xmasCount;
    }

public:
    WordSearchSolver(const std::vector<std::vector<char>>& g) : grid(g) {}

    int findWordOccurrences(const std::string& word) {
        int totalOccurrences = 0;
        
        // Possible search directions (including backwards)
        std::vector<std::pair<int, int>> directions = {
            {0,1},    // Right
            {1,0},    // Down
            {0,-1},   // Left
            {-1,0},   // Up
            {1,1},    // Down-Right
            {-1,-1},  // Up-Left
            {1,-1},   // Down-Left
            {-1,1}    // Up-Right
        };
        
        // Search from every cell
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                for (const auto& [dr, dc] : directions) {
                    if (matchWord(word, r, c, dr, dc)) {
                        totalOccurrences++;
                    }
                }
            }
        }
        
        return totalOccurrences;
    }

    int findXMASPatterns() {
        int xmasCount = 0;
        
        // Search from every cell (ignoring borders)
        for (int r = 1; r < grid.size() - 1; r++) {
            for (int c = 1; c < grid[0].size() - 1; c++) {
                xmasCount += checkXMASPattern(r, c);
            }
        }
        
        return xmasCount;
    }
};

int main() {
    // Read input from file
    std::ifstream inputFile("../inputs/day4.txt");
    if (!inputFile) {
        std::cerr << "Unable to open input file" << std::endl;
        return 1;
    }

    // Read grid from file
    std::vector<std::vector<char>> grid;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    // Solve word search
    WordSearchSolver solver(grid);

    // Part 1: Find XMAS occurrences
    int xmasOccurrences = solver.findWordOccurrences("XMAS");
    std::cout << "Part 1 - Number of XMAS occurrences: " << xmasOccurrences << std::endl;

    // Part 2: Find X-MAS patterns
    int xMasPatterns = solver.findXMASPatterns();
    std::cout << "Part 2 - Number of X-MAS patterns: " << xMasPatterns << std::endl;

    return 0;
}