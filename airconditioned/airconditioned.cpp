#include "airconditioned.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

namespace airconditioned {

template<typename T>
class interval {
public:
    T first() const { return _first; }
    T last() const { return _last; }
private:
    T _first, _last; // inclusive bound

    friend std::istream& operator>>(std::istream& is, interval& inter) {
        return is >> inter._first >> inter._last;
    }
};

using inter_t = interval<int>;

void solution(std::istream& in, std::ostream& out) {
    std::vector<inter_t> robots;
    int N;
    in >> N;

    robots.reserve(N);
    std::copy_n(std::istream_iterator<inter_t>(in), N, std::back_inserter(robots));

    std::sort(robots.begin(), robots.end(), [](const inter_t& a, const inter_t& b) {
        return a.last() > b.last();
    });

    size_t i = 0;
    for (; !robots.empty(); i++) {
        auto minIt = std::min_element(robots.cbegin(), robots.cend(), [](const inter_t& a, const inter_t& b) {
            return a.first() < b.first();
        });
        
        int last = minIt->last();

        //std::cerr << last << std::endl;

        robots.erase(minIt);

        auto fndIt = robots.begin();

        for(auto it = robots.rbegin(); it != robots.rend(); ++it){
            if (it->first() > last) {
                fndIt = it.base();
                break;
            } else {
                last = std::min(last, it->last());
            }
        }

        robots.erase(fndIt, robots.end());
    }
    out << i << std::endl;
}

} // namespace airconditioned
