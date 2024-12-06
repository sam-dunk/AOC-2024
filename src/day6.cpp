#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>

bool
check_loop (std::pair<size_t, size_t>& gpos, std::pair<size_t, size_t>& bpos, std::vector<std::vector<char>>& grid)
{
    // going to insert a barrier at bpos. Need to know if we are in a loop
    // will store barriers we have hit along with the direction we approached from
    // if this value repeats, we are in a loop

    char guard = '^';
    std::set<std::vector<size_t>> barriers;
    std::vector<std::vector<char>> grid_cpy = grid;
    grid_cpy[bpos.first][bpos.second] = '#';

    for(;;) {
        if (guard == '^') {
            if (gpos.first <= 0) break;
            if (grid_cpy[gpos.first - 1][gpos.second] == '#') {
                guard = '>';
                std::vector<size_t> b = {gpos.first, gpos.second, 1};
                if (barriers.find(b) != barriers.end()) return true;
                barriers.insert(b);
            } else {
                --gpos.first;
            }
        } else if (guard == '>') {
            if (gpos.second >= grid[0].size() - 1) break;
            if (grid_cpy[gpos.first][gpos.second + 1] == '#') {
                guard = 'v';
                std::vector<size_t> b = {gpos.first, gpos.second, 2};
                if (barriers.find(b) != barriers.end()) return true;
                barriers.insert(b);
            } else {
                ++gpos.second;
            }
        } else if (guard == 'v') {
            if (gpos.first >= grid.size() - 1) break;
            if (grid_cpy[gpos.first + 1][gpos.second] == '#') {
                guard = '<';
                std::vector<size_t> b = {gpos.first, gpos.second, 3};
                if (barriers.find(b) != barriers.end()) return true;
                barriers.insert(b);
            } else {
                ++gpos.first;
            }
        } else {
            if (gpos.second <= 0) break;
            if (grid_cpy[gpos.first][gpos.second - 1] == '#') {
                guard = '^';
                std::vector<size_t> b = {gpos.first, gpos.second, 4};
                if (barriers.find(b) != barriers.end()) return true;
                barriers.insert(b);
            } else {
                --gpos.second;
            }
        }
    }

    return false;
}

int 
main () 
{
    // Open input from file
    std::string filename = "../inputs/day6.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    // Read grid from file
    std::pair<size_t, size_t> orig_gpos = {0,0};
    std::vector<std::vector<char>> grid;
    std::string line;
    size_t y = 0;
    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
        
        auto it = std::find(row.begin(), row.end(), '^');
        if (it != row.end()) {
            size_t x = std::distance(row.begin(), it);
            orig_gpos.first = y;
            orig_gpos.second = x;
        }
        ++y;
    }

    file.close();

    // trace guard's path
    std::pair<size_t, size_t> gpos = orig_gpos;
    char guard = '^';
    std::set<std::pair<size_t, size_t>> visited;
    bool on_grid = true;
    do {
        if (guard == '^') {
            if (gpos.first <= 0) {
                on_grid = false;
                visited.insert(gpos);
            } else if (grid[gpos.first - 1][gpos.second] == '#') {
                guard = '>';
            } else {
                visited.insert(gpos);
                --gpos.first;
            }
        } else if (guard == '>') {
            if (gpos.second >= grid[0].size() - 1) {
                on_grid = false;
                visited.insert(gpos);
            } else if (grid[gpos.first][gpos.second + 1] == '#') {
                guard = 'v';
            } else {
                visited.insert(gpos);
                ++gpos.second;
            }
        } else if (guard == 'v') {
            if (gpos.first >= grid.size() - 1) {
                on_grid = false;
                visited.insert(gpos);
            } else if (grid[gpos.first + 1][gpos.second] == '#') {
                guard = '<';
            } else {
                visited.insert(gpos);
                ++gpos.first;
            }
        } else {
            if (gpos.second <= 0) {
                on_grid = false;
                visited.insert(gpos);
            } else if (grid[gpos.first][gpos.second - 1] == '#') {
                guard = '^';
            } else {
                visited.insert(gpos);
                --gpos.second;
            }
        }
    } while (on_grid);

    // compute locations for new barriers
    std::set<std::pair<size_t, size_t>> loop_positions;
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[0].size(); ++j) {
            if (i == orig_gpos.first && j == orig_gpos.second) continue;
            if (grid[i][j] == '#') continue;

            std::pair<size_t, size_t> bpos = {i, j};
            gpos = orig_gpos;
            if (check_loop(gpos, bpos, grid)) {
                loop_positions.insert(bpos);
            }
        }
    }

    // output result
    std::cout << "Part 1: " << visited.size() << std::endl;
    std::cout << "Part 2: " << loop_positions.size() << std::endl;

    return 0;
}