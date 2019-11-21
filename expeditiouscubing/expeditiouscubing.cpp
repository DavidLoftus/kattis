#include <cmath>
#include <algorithm>
#include <numeric>
#include "expeditiouscubing.hpp"

namespace expeditiouscubing {

int readTime(std::istream& in) {
    double x;
    in >> x;
    return static_cast<int>(std::round(x * 100));
}

void printTime(std::ostream& out, int x) {
    double y = x / 100.0;

    char str[64];
    sprintf(str, "%.02f", y);

    out << str;
}

double score(int t[5]) {
    int sum = std::accumulate(t, t+5, 0);

    auto p = std::minmax_element(t, t+5);
    sum -= *p.first + *p.second;

    return sum / 3.0;
}

void solution(std::istream& in, std::ostream& out) {

    int t[5];
    std::generate_n(t, 4, [&]{return readTime(in);});


    int target = readTime(in);

    t[4] = 2001;
    if (score(t) <= target) {
        out << "infinite\n";
        return;
    }

    t[4] = 99;
    if (score(t) > target) {
        out << "impossible\n";
        return;
    }

    for (t[4] = 2000; t[4] >= 100; --t[4]) {
        if (score(t) <= target) {
            printTime(out, t[4]);
            break;
        }
    }


}

} // namespace expeditiouscubing
