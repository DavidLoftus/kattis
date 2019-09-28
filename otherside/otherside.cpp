#include "otherside.hpp"

namespace otherside {

void solution(std::istream& in, std::ostream& out) {
    int w, s, c, k;
    in >> w >> s >> c >> k;

    int a = w + c;
    int b = s;

    if ((a <= 2*k && b <= k)
     || (b <= 2*k && a <= k)
     || a < k
     || b < k
     || (a == 0 && k > 0)
     || (b == 0 && k > 0)) {
        out << "YES\n";
    } else {
        out << "NO\n";
    }
}

} // namespace otherside
