#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>

std::vector<std::pair<size_t, size_t>> GetPalindromePairs(const std::vector<std::string> &strings) {
    std::unordered_map<std::string, size_t> str_idx;
    std::string reversed_copy;
    for (size_t i = 0; i < strings.size(); ++i) {
        reversed_copy = strings[i];
        std::reverse(reversed_copy.begin(), reversed_copy.end());
        str_idx[reversed_copy] = i;
    }

    std::vector<std::pair<size_t, size_t>> result;
    for (size_t word_idx = 0; word_idx < strings.size(); ++word_idx) {
        for (size_t word_partition = 0; word_partition < strings[word_idx].size(); ++word_partition) {
            std::string right_part = strings[word_idx].substr(word_partition + 1);
            std::string left_part  = strings[word_idx].substr(0, word_partition + 1);

            reversed_copy = right_part;
            std::reverse(reversed_copy.begin(), reversed_copy.end());
            if (right_part == reversed_copy) {
                auto it = str_idx.find(left_part);
                if (it != str_idx.end() && it->second != word_idx) {
                    result.emplace_back(word_idx, str_idx[left_part]);
                }
            }

            reversed_copy = left_part;
            std::reverse(reversed_copy.begin(), reversed_copy.end());
            if (left_part == reversed_copy) {
                auto it = str_idx.find(right_part);
                if (it != str_idx.end() && it->second != word_idx) {
                    result.emplace_back(str_idx[right_part], word_idx);
                }
            }

        }
    }

    return result;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    std::vector<std::string> strings(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> strings[i];
    }

    std::vector<std::pair<size_t, size_t>> palindrome_pairs = GetPalindromePairs(strings);
    std::sort(palindrome_pairs.begin(), palindrome_pairs.end());
    
    std::cout << palindrome_pairs.size() << "\n";
    for (size_t i = 0; i < palindrome_pairs.size(); ++i) {
        std::cout << palindrome_pairs[i].first + 1 << " " << palindrome_pairs[i].second + 1 << "\n";
    }

    return 0;
}