#include "candydivision.hpp"

#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>

namespace candydivision {

void solution(std::istream& in, std::ostream& out) {
    long long N;
    in >> N;

    auto sqrtN = static_cast<long long>(std::sqrt(N));

    // Store upper bound of factors so we can print them in the correct order
    std::vector<long long> factors;

    for(long long i = 1; i <= sqrtN; ++i) {
        if (N % i == 0) {
            out << (i - 1) << ' ';
            if (i * i != N) {
                factors.push_back(N / i);
            }
        }
    }

    for(auto it = factors.rbegin(); it != factors.rend(); ++it) {
        out << (*it - 1);
        if (std::next(it) != factors.rend()) {
            out << ' ';
        }
    }
    out << std::endl;
}

} // namespace candydivision
