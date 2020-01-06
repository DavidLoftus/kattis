#include <vector>
#include <memory>
#include <algorithm>
#include "insert.hpp"
#include <cstdint>

namespace insert {

class BinaryTree {
public:
    explicit BinaryTree(int data) : _data(data) {}

    BinaryTree* left() {
        return _left.get();
    }

    BinaryTree* right() {
        return _right.get();
    }

    const BinaryTree* left() const {
        _size = 0;
        return _left.get();
    }

    const BinaryTree* right() const {
        _size = 0;
        return _right.get();
    }

    int data() const {
        return _data;
    }

    BinaryTree* insert(int val) {
        _size = 0;
        if (val < _data) {
            if (_left) {
                return _left->insert(val);
            } else {
                _left = std::make_unique<BinaryTree>(val);
                return _left.get();
            }
        } else {
            if (_right) {
                return _right->insert(val);
            } else {
                _right = std::make_unique<BinaryTree>(val);
                return _right.get();
            }
        }
    }

    size_t size() const {
        if (_size != 0) {
            return _size;
        }

        _size = 1;
        if (_left)
            _size += _left->size();
        if (_right)
            _size += _right->size();
        return _size;
    }

private:
    int _data;
    mutable size_t _size = 0;
    std::unique_ptr<BinaryTree> _left, _right;
};

typedef int int128_t __attribute__((mode(TI)));
typedef unsigned int uint128_t __attribute__((mode(TI)));

uint128_t C(size_t n, size_t k) {
    static_assert(sizeof(uint128_t) >= 16, "fuck");
    double res = 1;
    for (size_t i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return static_cast<uint128_t>(res + 0.01);
}

int128_t solve(const BinaryTree& sequence) {
    size_t leftSz = 0;
    uint128_t leftPermutations = 1;
    if (sequence.left()) {
        leftSz = sequence.left()->size();
        leftPermutations = solve(*sequence.left());
    }

    size_t rightSz = 0;
    uint128_t rightPermutations = 1;
    if (sequence.right()) {
        rightSz = sequence.right()->size();
        rightPermutations = solve(*sequence.right());
    }

    uint128_t ret = C(leftSz + rightSz, leftSz) * leftPermutations * rightPermutations;

    //std::cerr << sequence.data() << ": " << ret << std::endl;

    return ret;
}

uint128_t solve(const std::vector<int>& sequence) {
    BinaryTree root{sequence.front()};

    std::for_each(sequence.begin()+1, sequence.end(), [&](int val) {
        root.insert(val);
    });

    std::cerr << root.size() << std::endl;

    return solve(root);
}

std::ostream& operator<<(std::ostream& os, uint128_t x) {
    std::string digits;
    while (x) {
        digits.push_back('0' + x % 10);
        x /= 10;
    }
    std::reverse(digits.begin(), digits.end());
    return os << digits;
}

void solution(std::istream& in, std::ostream& out) {
    while (true) {
        int len;
        in >> len;

        if (len == 0) {
            break;
        }

        std::vector<int> sequence;
        sequence.reserve(len);
        for (int i = 0; i < len; ++i) {
            int n;
            in >> n;
            sequence.push_back(n);
        }

        uint128_t ans = solve(sequence);

        out << ans << '\n';
    }
}

} // namespace insert
