#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

/// \brief Получает индекс в переданном векторе по заданным x, n и предпосчитанному корню от n.
inline int64_t AcquireIndex(int64_t x, int64_t n, int64_t n_sqr, const std::vector<int64_t> & belows) {
    if (x <= n) {
        return x - 1;
    }
    return static_cast<int64_t>(belows.size() - (n_sqr / x)); 
}

/// \brief Предподсчитывает вектор элементов при заданном n, чтобы впоследствии заполнить DP вектор. 
inline std::vector<int64_t> PrecalcBelows(int64_t n) {
    std::vector<int64_t> belows;
    for (int64_t i = 1; i * i <= n; ++i) {
        belows.push_back(n / i);
        belows.push_back(i);
    }
    sort(belows.begin(), belows.end());
    belows.erase(unique(belows.begin(), belows.end()), belows.end());

    return belows;
}

int main() {
    int64_t n = 0;
    std::cin >> n;

    auto belows = PrecalcBelows(n);
    std::vector<int64_t> dp(belows.size());

    for (uint64_t i = 0; i < belows.size(); ++i) {
        dp[i] = belows[i];
    }

    int primes = 0;
    auto n_sqrt = static_cast<int64_t>(sqrt(static_cast<double>(n)));
    for (int64_t p = 2; p * p <= n; ++p) {
        if (dp[AcquireIndex(p, n_sqrt, n, belows)] != dp[AcquireIndex(p - 1, n_sqrt, n, belows)]) {
            ++primes;
            for (size_t i = belows.size(); i > 0; --i) {
                if (belows[i - 1] < p * p) {
                    break;
                }
                dp[i - 1] -= dp[AcquireIndex(belows[i - 1] / p, n_sqrt, n, belows)] - primes;
            }
        }
    }

    std::cout << dp[AcquireIndex(n, n_sqrt, n, belows)] - 1;
}
