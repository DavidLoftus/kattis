#include "loowater.hpp"

#include <vector>
#include <algorithm>
#include <iterator>

namespace loowater {

void solution(std::istream& in, std::ostream& out) {
    while (true) {

        int n, m;
        in >> n >> m; in.ignore();

        if (n == 0 && m == 0) {
            break;
        }

        std::vector<int> dragonHeads;
        dragonHeads.reserve(n);
        std::copy_n(std::istream_iterator<int>(in), n, std::back_inserter(dragonHeads));

        std::vector<int> knights;
        knights.reserve(m);
        std::copy_n(std::istream_iterator<int>(in), m, std::back_inserter(knights));

        if (dragonHeads.size() > knights.size()) {
            out << "Loowater is doomed!\n";
            continue;
        }

        std::sort(dragonHeads.begin(), dragonHeads.end());
        std::sort(knights.begin(), knights.end());

        int cost = 0;

        bool doomed = false;

        auto knightIt = knights.begin();
        for (int head : dragonHeads) {
            // Search for smallest knight that can cut this head.
            knightIt = std::lower_bound(knightIt, knights.end(), head);
            if (knightIt == knights.end()) {
                doomed = true;
                break;
            }

            cost += *knightIt;
            ++knightIt;
        }

        if (doomed) {
            out << "Loowater is doomed!\n";
        } else {
            out << cost << '\n';
        }
    }
}

} // namespace loowater
