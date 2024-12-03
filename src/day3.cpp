#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

// parses all mul operations in text
std::vector<std::string> parse_text(const std::string& text) {
    // setup regex
    std::regex pattern(R"(mul\(\d+,\d+\))");
    std::vector<std::string> matches;

    // parse every well-formatted mul
    std::sregex_iterator begin(text.begin(), text.end(), pattern);
    std::sregex_iterator end;
    for (auto i = begin; i != end; ++i) {
        matches.push_back(i->str());
    }

    return matches;
}

// parses integers from each mul and accumulates result
void mult_sum(std::vector<std::string>& matches) {
    // setup regex
    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::smatch smatch;

    // accumulate final sum
    long long acc = 0;
    for (std::string match : matches) {
        if (std::regex_search(match, smatch, pattern)) {
            int num1 = std::stoi(smatch[1].str());
            int num2 = std::stoi(smatch[2].str());
            acc = (num1 < 1000 && num2 < 1000) ? acc + num1 * num2 : acc;
        }
    }

    // print result
    std::cout << "Part 1 Result: " << acc << std::endl;
}

// parses mul operations in regions of text where computations are enabled
std::vector<std::string> parse_text_conditional(const std::string& text) {
    std::vector<std::string> matches;
    bool enabled = true;
    std::string suffix = text;
    size_t pos = 0;

    while (pos < text.size()) {
        if (enabled) {
            // Find the next "don't()" if enabled
            size_t dont_pos = text.find("don't()", pos);
            if (dont_pos == std::string::npos) {
                // no "don't()" in remainder of string
                std::string remainder = text.substr(pos);
                std::vector<std::string> new_matches = parse_text(remainder);
                matches.insert(matches.end(), new_matches.begin(), new_matches.end());
                break;
            }

            // Handle everything up to the next "don't()"
            std::string enabled_text = text.substr(pos, dont_pos - pos);
            std::vector<std::string> new_matches = parse_text(enabled_text);
            matches.insert(matches.end(), new_matches.begin(), new_matches.end());

            // Update position to continue after "don't()"
            pos = dont_pos + 7;
            enabled = false;
        } else {
            // Find the next "do()" if disabled
            size_t do_pos = text.find("do()", pos);
            if (do_pos == std::string::npos) {
                // no "do()" in remainder of string
                break;
            }

            // Update position to continue after "do()"
            pos = do_pos + 4;
            enabled = true;
        }
    }

    return matches;
}

int main() {
    // read content of file
    std::ifstream file ("../inputs/day3.txt");
    std::string text;
    file.seekg(0, std::ios::end);
    text.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&text[0], text.size());
    file.close();

    // compute part 1 solution
    std::vector<std::string> matches = parse_text(text);
    mult_sum(matches);

    // compute part 2 solution
    std::vector<std::string> cond_matches = parse_text_conditional(text);
    mult_sum(cond_matches);
}