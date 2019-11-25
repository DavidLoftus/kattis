#include "glyphrecognition.hpp"

#include <vector>
#include <iterator>
#include <algorithm>
#include <tuple>
#include <cmath>

namespace glyphrecognition {

struct Vertex {
    int x, y;
};

std::istream& operator>>(std::istream& in, Vertex& vert) {
    in >> vert.x >> vert.y; in.ignore();
    return in;
}

double GetAngle(Vertex vertex) {
    return std::atan(static_cast<double>(vertex.x) / vertex.y);
}

double PolygonSize(Vertex vertex, int k) {
    return vertex.x + vertex.y / std::tan(M_PI_2 / k);
}

std::pair<double,double> GetPolygonBounds(const std::vector<Vertex>& vertices, int k) {
    double minSize = std::numeric_limits<double>::max();
    double maxSize = std::numeric_limits<double>::min();
    for (auto& vertex : vertices) {
        double size = PolygonSize(vertex, k);
        if (size < minSize) {
            minSize = size;
        }
        if (size > maxSize ) {
            maxSize  = size;
        }
    }
    return std::make_pair(minSize, maxSize);
}

double GetScore(const std::vector<Vertex>& vertices, int k) {
    double innerSize, outerSize;
    std::tie(innerSize, outerSize) = GetPolygonBounds(vertices, k);
    double lengthRatio = innerSize / outerSize;
    return lengthRatio * lengthRatio;
}

void solution(std::istream& in, std::ostream& out) {

    int n;
    in >> n; in.ignore();

    std::vector<Vertex> vertices{ std::istream_iterator<Vertex>(in), std::istream_iterator<Vertex>() };

    std::vector<double> scores(6);
    for (int k = 3; k <= 8; ++k) {
        scores[k-3] = GetScore(vertices, k);
    }

    auto it = std::max_element(scores.begin(), scores.end());

    int k = std::distance(scores.begin(), it) + 3;
    out << k << ' ' << *it << std::endl;


}

} // namespace glyphrecognition
