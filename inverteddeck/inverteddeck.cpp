#include <vector>
#include <iterator>
#include <algorithm>
#include "inverteddeck.hpp"

namespace inverteddeck {

void solution(std::istream& in, std::ostream& out) {

    int n;
    in >> n;

    std::vector<int> cards{std::istream_iterator<int>(in), std::istream_iterator<int>()};


    auto sortedCards = cards;
    std::sort(sortedCards.begin(), sortedCards.end());

    int left = 0, right = cards.size() - 1;

    while (left < cards.size() && cards[left] == sortedCards[left]) {
        ++left;
    }

    if (left == cards.size()) {
        left = right = cards.size()/2;
    } else {
        while (cards[right] == sortedCards[right]) {
            --right;
        }

        std::reverse(cards.begin() + left, cards.begin() + right + 1);

        if (cards != sortedCards) {
            out << "impossible\n";
            return;
        }
    }

    out << (left + 1) << ' ' << (right + 1) << std::endl;

}

} // namespace inverteddeck
