#include "unusualdarts.hpp"

#include <array>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <vector>

namespace unusualdarts {

struct Point {
    double x, y;
};

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y; is.ignore();
    return is;
}

using DartsList = std::array<Point, 7>;
using Permutation = std::vector<int>;

std::ostream& operator<<(std::ostream& os, const Permutation& p) {
    for (auto it = p.begin(); it != p.end(); ++it) {
        os << 1 + *it;
        if (it+1 != p.end()) {
            os << ' ';
        }
    }
    return os;
}

class PermutationIterator {
public:
    PermutationIterator() = default;
    explicit PermutationIterator(size_t sz) : perm_(sz) {
        std::iota(perm_.begin(), perm_.end(), 0);
    }

    PermutationIterator begin() const {
        return *this;
    }

    PermutationIterator end() const {
        return PermutationIterator();
    }

    bool operator!=(const PermutationIterator& other) {
        return perm_ != other.perm_;
    }

    PermutationIterator& operator++() {
        if (perm_.empty()) {
            return *this;
        }

        auto firstIt = perm_.end();
        for(auto it = 1 + perm_.rbegin(); it != perm_.rend(); ++it) {
            if (*it < *(it-1)) {
                firstIt = it.base() - 1;
                break;
            }
        }

        if (firstIt == perm_.end()) {
            perm_.clear();
            return *this;
        }

        auto ceilingIt = 1 + firstIt;
        for (auto it = 2 + firstIt; it != perm_.end(); ++it) {
            if (*it > *firstIt && *it < *ceilingIt) {
                ceilingIt = it;
            }
        }

        std::iter_swap(firstIt, ceilingIt);

        std::sort(firstIt+1, perm_.end());

        return *this;
    }

    const Permutation& operator*() const {
        return perm_;
    }

private:
    Permutation perm_;
};

template<typename Int1, typename Int2>
inline Int1 mod(Int1 a, Int2 m) {
    return (m + (a % m)) % m;
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    float val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) {
        return true;
    }

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}

bool isSimplePolygon(const DartsList& points, const Permutation& perm) {
    for (unsigned i = 0; i+1 < perm.size(); ++i) {
        Point p1 = points[perm[i]];
        Point q1 = points[perm[i+1]];

        for (unsigned j = i+2; j < perm.size(); ++j) {
            if (i == 0 && j == perm.size() - 1) {
                continue;
            }

            Point p2 = points[perm[j]];
            Point q2 = points[perm[mod(j+1, points.size())]];

            if (doIntersect(p1, q1, p2, q2)) {
                return false;
            }
        }
    }
    return true;
}

double findArea(const DartsList& darts, const Permutation& perm) {
    // Shoelace formula
    double area = 0.0;
    for (unsigned i = 0; i+1 < darts.size(); ++i) {
        const Point& dart1 = darts[perm[i]];
        const Point& dart2 = darts[perm[i+1]];
        area += dart1.x * dart2.y;
    }
    area += darts[perm.back()].x * darts[perm.front()].y;

    for (unsigned i = 0; i+1 < darts.size(); ++i) {
        const Point& dart1 = darts[perm[i]];
        const Point& dart2 = darts[perm[i+1]];
        area -= dart2.x * dart1.y;
    }
    area -= darts[perm.front()].x * darts[perm.back()].y;

    return std::abs(area)/2;
}

Permutation findPolygonOrder(const DartsList& darts, double probability) {
    PermutationIterator permutations(darts.size());
    for(const Permutation& perm : permutations) {
        // These permutations are identical polygons to previous polygons
        if (perm.front() != 0) {
            break;
        }

        double area = findArea(darts, perm);
        double prob = area / 4;
        prob = prob*prob*prob;

        double diff = std::abs( prob - probability );


        if (diff <= 0.00001) {
            if (isSimplePolygon(darts, perm)) {
                return perm;
            }
        }
    }

    throw std::runtime_error("fuck");
}


void solution(std::istream& in, std::ostream& out) {
    DartsList alicesDarts;

    int n;
    in >> n;

    for (int i = 0; i < n; ++i) {
        std::copy_n(std::istream_iterator<Point>(in), alicesDarts.size(), alicesDarts.begin());

        double prob;
        in >> prob; in.ignore();

        Permutation dartsOrder = findPolygonOrder(alicesDarts, prob);

        out << dartsOrder << std::endl;
    }
}

} // namespace unusualdarts
