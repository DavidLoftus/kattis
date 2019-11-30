#include "gnollhypothesis.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>

namespace gnollhypothesis {


long double binomialCoeff(int n, int k)
{
    if (k > n) return 0;
    if (k < 0) return 0;
    long double res = 1;

    // Since C(n, k) = C(n, n-k)
    if ( k > n - k )
        k = n - k;

    // Calculate value of
    // [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1]
    for (int i = 0; i < k; ++i)
    {
        res *= (n - i);
        //std::cerr  << "n - i = " << (n-i) << std::endl;
        res /= (i + 1);
    }

    return res;
}

long double getProbability(int n, int k, int j) {
    return binomialCoeff(n - j - 1, k - 1) / binomialCoeff(n, k);
}

void solution(std::istream& in, std::ostream& out) {
    
    int n, k;
    in >> n >> k;

    std::vector<double> probabilities;
    probabilities.reserve(n);

    std::copy_n(std::istream_iterator<double>(in), n, std::back_inserter(probabilities));

    std::vector<long double> newProbabilities(n, 0.0);

    for (int j = 0; j <= n - k; ++j) {
        long double probability = getProbability(n, k, j);

        for (int i = 0; i < n; ++i) {
            int iMinusJ = (n + i - j) % n;
            newProbabilities[i] += probability * probabilities[iMinusJ];
        }
    }

    out << std::setprecision(7);
    for (double s : newProbabilities) {
        out << s << ' ';
    }
    out << '\n';
}

} // namespace gnollhypothesis
