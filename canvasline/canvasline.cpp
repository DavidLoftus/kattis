#include "canvasline.hpp"
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>

namespace canvasline {

struct Canvas {
    int left;
    int right;
};

std::istream& operator>>(std::istream& is, Canvas& c){
    return is >> c.left >> c.right;
}

void solution(std::istream& in, std::ostream& out) {
    int n;
    in >> n;

    std::vector<Canvas> canvases;
    canvases.reserve(n);
    std::copy_n(std::istream_iterator<Canvas>(in), n, std::back_inserter(canvases));

    int p;
    in >> p;

    std::set<int> pegs;
    std::copy_n(std::istream_iterator<int>(in), p, std::inserter(pegs, pegs.begin()));

    std::vector<int> newPegs;

    auto insertPegIn = [&](int pos) {
        pegs.insert(pos);
        newPegs.push_back(pos);
    };

    auto insertPegsIn = [&](Canvas c, int n) {
        int pos = c.left+1;
        for (int i = 0; i < n; ++i) {
            while(pegs.count(pos) > 0) {
                ++pos;
            }
            insertPegIn(pos++);
        }
    };

    auto countPegsInCanvas = [&](Canvas c){
        auto leftIt = pegs.lower_bound(c.left);
        auto rightIt = pegs.upper_bound(c.right);
        return std::distance(leftIt, rightIt);
    };

    for (auto it = canvases.begin(); it != canvases.end(); ++it) {
        Canvas canvas = *it;

        int numPegs = countPegsInCanvas(canvas);

        if (numPegs > 2) {
            out << "impossible\n";
            return;
        } else if (numPegs == 2)  {
            continue;
        } else {
            if (pegs.count(canvas.right) == 0) {
                auto nextIt = std::next(it);
                if (nextIt == canvases.end() || nextIt->left > canvas.right || countPegsInCanvas(*nextIt) < 2) {
                    insertPegIn(canvas.right);
                    numPegs++;
                }
            }
            insertPegsIn(canvas, 2-numPegs);
        }
    }

    out << newPegs.size() << '\n';
    for (int peg : newPegs) {
        out << peg << ' ';
    }

}

} // namespace canvasline
