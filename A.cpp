#include <iostream>
#include <vector>

std::vector<int> PrefixFunction(const std::string & input) {
  int n = static_cast<int>(input.length());
  std::vector<int> pi(n);

  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && input[i] != input[j]) {
      j = pi[j - 1];
    }
    if (input[i] == input[j]) {
      ++j;
    }
    pi[i] = j;
  }

  return pi;
}

int main() {
  std::string input_string;
  std::string prefix;
  std::cin >> input_string >> prefix;

  std::string concatenated = prefix + '#' + input_string;
  std::vector<int> prefix_s = PrefixFunction(concatenated);

  for (size_t i = prefix.size() + 1; i < concatenated.size(); ++i) {
    if (static_cast<uint64_t>(prefix_s[i]) == prefix.size()) {
      std::cout << i - 2 * prefix.size() << "\n";
    }
  }
  
  return 0;
}
