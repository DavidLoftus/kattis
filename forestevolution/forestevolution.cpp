#include "forestevolution.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

namespace forestevolution {

struct Point
{
    double x, y;

    bool operator==(const Point& b) const
    {
        return x == b.x && y == b.y;
    }

    bool operator!=(const Point& b) const
    {
        return !(*this == b);
    }
};

constexpr double EquityTolerance = 0.000000001;

inline bool IsEqual(double d1, double d2)
{
    return std::abs(d1-d2) <= EquityTolerance;
}

std::pair<bool,Point> LineLineIntersection(Point l1p1, Point l1p2, Point l2p1, Point l2p2)
{
    double A1 = l1p2.y - l1p1.y;
    double B1 = l1p1.x - l1p2.x;
    double C1 = A1 * l1p1.x + B1 * l1p1.y;

    double A2 = l2p2.y - l2p1.y;
    double B2 = l2p1.x - l2p2.x;
    double C2 = A2 * l2p1.x + B2 * l2p1.y;

    //lines are parallel
    double det = A1 * B2 - A2 * B1;
    if (IsEqual(det, 0))
    {
        return std::make_pair(false, Point{}); //parallel lines
    }
    else
    {
        double x = (B2 * C1 - B1 * C2) / det;
        double y = (A1 * C2 - A2 * C1) / det;
        bool online1 = ((std::min(l1p1.x, l1p2.x) < x || IsEqual(std::min(l1p1.x, l1p2.x), x))
                     && (std::max(l1p1.x, l1p2.x) > x || IsEqual(std::max(l1p1.x, l1p2.x), x))
                     && (std::min(l1p1.y, l1p2.y) < y || IsEqual(std::min(l1p1.y, l1p2.y), y))
                     && (std::max(l1p1.y, l1p2.y) > y || IsEqual(std::max(l1p1.y, l1p2.y), y))
        );
        bool online2 = ((std::min(l2p1.x, l2p2.x) < x || IsEqual(std::min(l2p1.x, l2p2.x), x))
                     && (std::max(l2p1.x, l2p2.x) > x || IsEqual(std::max(l2p1.x, l2p2.x), x))
                     && (std::min(l2p1.y, l2p2.y) < y || IsEqual(std::min(l2p1.y, l2p2.y), y))
                     && (std::max(l2p1.y, l2p2.y) > y || IsEqual(std::max(l2p1.y, l2p2.y), y))
        );

        if (online1 && online2)
            return std::make_pair(true, Point{x, y});
    }
    return std::make_pair(false, Point{}); //intersection is at out of at least one segment.
}

struct Polygon {
    std::vector<Point> points;

    bool contains(Point p) const {
        bool result = false;
        for (unsigned i = 0, j = points.size() - 1; i < points.size(); j = i++) {
            if ((points[i].y > p.y) != (points[j].y > p.y) &&
                (p.x < (points[j].x - points[i].x) * (p.y - points[i].y) / (points[j].y-points[i].y) + points[i].x)) {
                result = !result;
            }
        }
        return result;
    }
    
    double area() const {
        // Shoelace formula
        double area = 0.0;
        for (unsigned i = 0; i+1 < points.size(); ++i) {
            const Point& dart1 = points[i];
            const Point& dart2 = points[i+1];
            area += dart1.x * dart2.y;
        }
        area += points.back().x * points.front().y;

        for (unsigned i = 0; i+1 < points.size(); ++i) {
            const Point& dart1 = points[i];
            const Point& dart2 = points[i+1];
            area -= dart2.x * dart1.y;
        }
        area -= points.front().x * points.back().y;

        return std::abs(area)/2;
    }

    Polygon intersect(const Polygon& other) const {
        // Create an empty polygon as P
        Polygon poly;

        // Add all corners of Polygon1 that is inside Polygon2 to P
        for (Point p : points) {
            if (other.contains(p)) {
                poly.points.push_back(p);
            }
        }

        // Add all corners of Polygon2 that is inside Polygon1 to P
        for (Point p : other.points) {
            if (contains(p)) {
                poly.points.push_back(p);
            }
        }

        // Add all intersection points to P
        for (unsigned ip = 0, iq = points.size() - 1; ip < points.size(); iq = ip++) {
            Point p1 = points[ip];
            Point q1 = points[iq];
            for (unsigned jp = 0, jq = other.points.size() - 1; jp < other.points.size(); jq = jp++) {
                Point p2 = other.points[jp];
                Point q2 = other.points[jq];

                std::pair<bool,Point> pair = LineLineIntersection(p1,q1, p2, q2);
                if (pair.first) {
                    poly.points.push_back(pair.second);
                }
            }
        }

        // Order all points in the P counter-clockwise.
        Point mid{0,0};
        for (Point p : poly.points) {
            mid.x += p.x;
            mid.y += p.y;
        }
        mid.x /= poly.points.size();
        mid.y /= poly.points.size();

        std::sort(poly.points.begin(), poly.points.end(), [mid](Point a, Point b){
            return atan2(a.y - mid.y, a.x - mid.x) < atan2(b.y - mid.y, b.x - mid.x);
        });

        return poly;
    }
};

Polygon JarvisMarch(const std::vector<Point>& points)
{
    std::vector<Point> hull_points;

    if(points.empty())
        return Polygon{hull_points};

    // Left most point
    auto first_point_it = std::min_element(points.begin(), points.end(), [](const Point& a, const Point& b){ return a.x < b.x; });

    auto next_point_it = first_point_it;
    do
    {
        hull_points.push_back(*next_point_it);

        const Point& p1 = hull_points.back();

        // Largest internal angle
        next_point_it = std::max_element(
                points.begin(),
                points.end(),
                [p1](const Point& p2, const Point& p3){
                    return (p1 == p2) || (p2.x - p1.x) * (p3.y - p1.y) > (p3.x - p1.x) * (p2.y - p1.y);
                }
        );
    } while(*next_point_it != *first_point_it);

    return Polygon{hull_points};
}

void solution(std::istream& in, std::ostream& out) {
    int p, a;
    in >> p >> a;

    std::vector<Point> pine(p), aspen(a);

    std::generate(pine.begin(), pine.end(), [&]{
       double x, y;
       in >> x >> y; in.ignore();
       return Point{x, y};
    });

    std::generate(aspen.begin(), aspen.end(), [&]{
        double x, y;
        in >> x >> y; in.ignore();
        return Point{x, y};
    });

    if (p < 3 || a < 3) {
        out << 0.0 << std::endl;
        return;
    }

    Polygon pine_hull = JarvisMarch(pine);
    Polygon aspen_hull = JarvisMarch(aspen);

    if (pine_hull.points.size() < 3 || aspen_hull.points.size() < 3) {
        out << 0.0 << std::endl;
        return;
    }

    Polygon intersect = pine_hull.intersect(aspen_hull);

    if (intersect.points.size() < 3) {
        out << 0.0 << std::endl;
        return;
    }

    out << intersect.area() << std::endl;
}

} // namespace forestevolution
