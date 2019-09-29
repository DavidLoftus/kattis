#include "divljak.hpp"

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <string_view>

namespace divljak {

const unsigned PRIME_BASE = 257;
const unsigned PRIME_MOD = 1000000007;

unsigned hash(const std::string& s)
{
    long long ret = 0;
    for (char c : s)
    {
        ret = ret*PRIME_BASE + c;
        ret %= PRIME_MOD; //don't overflow
    }
    return ret;
}

size_t rabin_karp(const std::string& needle, const std::string& haystack, long long hash1)
{
    //I'm using long longs to avoid overflow
    long long hash2 = 0;

    //you could use exponentiation by squaring for extra speed
    long long power = 1;
    for (size_t i = 0; i < needle.size(); i++)
        power = (power * PRIME_BASE) % PRIME_MOD;

    for (size_t i = 0; i < haystack.size(); i++)
    {
        //add the last letter
        hash2 = hash2*PRIME_BASE + haystack[i];
        hash2 %= PRIME_MOD;

        //remove the first character, if needed
        if (i >= needle.size())
        {
            hash2 -= power * haystack[i-needle.size()] % PRIME_MOD;
            if (hash2 < 0) //negative can be made positive with mod
                hash2 += PRIME_MOD;
        }

        //match?
        if (i >= needle.size()-1 && hash1 == hash2)
            return i - (needle.size()-1);
    }

    return std::string::npos;
}

class Barbarian {
public:
    explicit Barbarian(std::string word) : word_(std::move(word)) {
        word_hash_ = hash(word_);
    }

    int hits() const {
        return hits_;
    }

    unsigned handled() const {
        return handled_;
    }

    void visit(const std::string& str) {
        if (rabin_karp(word_, str, word_hash_) != std::string::npos) {
            ++hits_;
        }
        ++handled_;
    }

private:
    int hits_ = 0;
    unsigned handled_ = 0;
    std::string word_;
    unsigned word_hash_;
};

void solution(std::istream& in, std::ostream& out) {
    int n;
    in >> n;

    std::vector<Barbarian> barbarians;
    barbarians.reserve(n);

    std::generate_n(std::back_inserter(barbarians), n, [&]{
        std::string word;
        in >> word;
        return Barbarian(std::move(word));
    });

    // List of queries of type 1
    std::vector<std::string> queries;

    int q;
    in >> q;

    for (int i = 0; i < q; ++i) {
        int t;
        in >> t;

        if (t == 1) {
            queries.emplace_back();
            in >> queries.back();
        } else if (t == 2) {
            int s;
            in >> s;

            Barbarian& barb = barbarians[s - 1];

            std::for_each(
                    std::next(queries.begin(), barb.handled()),
                    queries.end(),
                    [&](const std::string& word) {
                        barb.visit(word);
                    });

            if (barb.handled() != queries.size()) {
                throw std::runtime_error("fuck");
            }

            out << barb.hits() << '\n';
        } else {
            throw std::runtime_error("bad type.");
        }
    }
}

} // namespace divljak
