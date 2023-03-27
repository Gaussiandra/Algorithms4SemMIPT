#include <iostream>
#include <vector>
#include <map>

std::vector<int> SuffixArray (std::string &s) {
    int n = static_cast<int>(s.size());
    std::vector<int> c(n);
    std::vector<int> p(n);
    s.push_back(0); 

    int sort_counter = 0;
    int n_classes = 0; 
    
    std::map<int, std::vector<int>> dict;
    for (int i = 0; i < n; i++) {
        dict[s[i]].push_back(i);
    }
    
    for (auto &x : dict) {
        for (int u : x.second) {
            c[u] = n_classes, p[sort_counter++] = u;
        }
        n_classes++;
    }
    
    for (int l = 1; n_classes < n; l++) {
        std::vector<std::vector<int> > arr_to_sort(n_classes);
        std::vector<int> new_classes(n);
        int d = (1 << l) / 2;
        int class_one = sort_counter = 0;
        
        for (int i = 0; i < n; i++) {
            int k = (p[i]-d+n)%n;
            arr_to_sort[c[k]].push_back(k);
        }
        
        for (int i = 0; i < n_classes; i++) {
            for (size_t j = 0; j < arr_to_sort[i].size(); j++) {
                int prev_check = (arr_to_sort[i][j] + d);
                int cur_check  = (arr_to_sort[i][j - 1] + d);
                bool to_increase = c[prev_check % n] != c[cur_check % n];
                if (j == 0 || to_increase) {
                    class_one++;
                }
                new_classes[arr_to_sort[i][j]] = class_one - 1;
                p[sort_counter++] = arr_to_sort[i][j];
            }
        }
        
        c = new_classes;
        n_classes = class_one;
    }
    
    s.pop_back();
    return { p.begin() + 1, p.end() };
}

int main() {
    std::string input;
    std::getline(std::cin, input);

    std::vector<int> suf_arr = SuffixArray(input);
    for (size_t i = 0; i < suf_arr.size(); ++i) {
        std::cout << suf_arr[i] + 1 << " ";
    }

    return 0;
}