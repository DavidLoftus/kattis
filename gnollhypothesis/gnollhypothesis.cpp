#include "gnollhypothesis.hpp"
#include <vector>
#include <algorithm>
#include <iterator>

namespace gnollhypothesis {

void solution(std::istream& in, std::ostream& out) {
    
    int n, k;
    in >> n >> k;

    std::vector<double> probabilities;
    probabilities.reserve(n);

    std::copy_n(std::istream_iterator<double>(in), n, std::back_inserter(probabilities));

    std::vector<double> newProbabilities(n, 0.0);

    

    for (double s : newProbabilities) {
        out << s << ' ';
    }
    out << '\n';
}

} // namespace gnollhypothesis
