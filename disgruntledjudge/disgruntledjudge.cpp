#include "disgruntledjudge.hpp"

#include <vector>
#include <algorithm>

namespace disgruntledjudge {

// Euclidean division modulo
int mod(int x, int m) {
    return (m + (x % m)) % m;
}

const int modulus = 10001;

std::vector<int> predict(const std::vector<int>& input) {
    if (input.size() < 3) {
        throw std::invalid_argument("can't handle when input.size() < 3");
    }

    int delta1 = mod(input[1] - input[0], modulus);
    int delta2 = mod(input[2] - input[1], modulus);

    int aSolution = -1, bSolution = -1;
    bool foundSolution = false;

    for (int a = 0; a < modulus; ++a) {
        int aSquared = mod(a*a,modulus);
        if (delta2 != mod(aSquared*delta1, modulus)) {
            continue;
        }
        for (int b = 0; b < modulus; ++b) {
            foundSolution = true;
            for (int i = 1; i < input.size(); ++i) {
                if (input[i] != mod(aSquared*input[i-1] + a*b + b, modulus)) {
                    foundSolution = false;
                    break;
                }
            }
            if (!foundSolution) {
                continue;
            }

            aSolution = a;
            bSolution = b;
            break;
        }
        if (foundSolution) {
            break;
        }
    }

    if (!foundSolution) {
        throw std::runtime_error("couldn't find solution.");
    }

    std::vector<int> output( input.size(), 0 );
    std::transform(input.cbegin(),
                   input.cend(),
                   output.begin(),
                   [aSolution,bSolution](int x) {
                        return mod(aSolution*x + bSolution, modulus);
                   }
    );

    return output;
}

void solution(std::istream& in, std::ostream& out) {
    int n;
    in >> n;

    std::vector<int> input( n, 0 );

    for (int& x : input) {
        in >> x;
    }

    std::vector<int> output = predict(input);

    for (int x : output) {
        out << x << '\n';
    }
}

} // namespace disgruntledjudge
