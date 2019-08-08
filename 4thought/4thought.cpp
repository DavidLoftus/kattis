#include "4thought.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <array>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <unordered_map>

namespace _4thought {

enum class Operator : char {
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/'
};

class FourFours {
public:
    FourFours() {
        for (auto op0 : {Operator::ADD, Operator::SUB, Operator::MUL, Operator::DIV}) {
            for (auto op1 : {Operator::ADD, Operator::SUB, Operator::MUL, Operator::DIV}) {
                for (auto op2 : {Operator::ADD, Operator::SUB, Operator::MUL, Operator::DIV}) {
                    int n = compute({op0, op1, op2});
                    _cached[n] = makeEquation(n, op0, op1, op2);
                }
            }
        }
    }

    std::string operator[](int i) const {
        auto p = _cached.find(i);
        if (p == _cached.end()) {
            return "no solution";
        }
        return p->second;
    }


private:

    static int compute(std::array<Operator, 3> ops) {
        int arr[] = {4, 4, 4, 4};

        int lastVal = std::numeric_limits<int>::min();

        for(size_t i = 0; i < ops.size(); ++i) {
            if (ops[i] == Operator::MUL) {
                arr[i] = arr[i+1] = arr[i] * arr[i+1];
                lastVal = arr[i];
            } else if (ops[i] == Operator::DIV) {
                arr[i] = arr[i+1] = arr[i] / arr[i+1];
                lastVal = arr[i];
            }
        }

        for(size_t i = 0; i < ops.size(); ++i) {
            if (ops[i] == Operator::ADD) {
                arr[i] = arr[i+1] = arr[i] + arr[i+1];
                lastVal = arr[i];
            } else if (ops[i] == Operator::SUB) {
                arr[i] = arr[i+1] = arr[i] - arr[i+1];
                lastVal = arr[i];
            }
        }

        assert(lastVal != std::numeric_limits<int>::min());

        return lastVal;
    }

    static std::string makeEquation(int n, Operator op0, Operator op1, Operator op2) {
        char buff[200];
        snprintf(buff, sizeof(buff), "4 %c 4 %c 4 %c 4 = %d", (char)op0, (char)op1, (char)op2, n);
        return buff;
    }

    std::unordered_map<int, std::string> _cached;
};

void solution(std::istream& in, std::ostream& out) {
    int m;
    in >> m; in.ignore();

    FourFours f;

    std::generate_n(std::ostream_iterator<std::string>(out, "\n"), m, [&]{
        int n;
        in >> n;

        return f[n];
    });

}

} // namespace _4thought
