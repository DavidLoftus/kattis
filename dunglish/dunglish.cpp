#include "dunglish.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <algorithm>

namespace dunglish {

class DictEntry {
public:
    DictEntry() = default;

    void AddTranslation(const std::string& s, bool correct) {

        if (_total == 0) {
            _first = s;
        }

        ++_total;
        if (correct) {
            ++_total_correct;
        }
    }

    const std::string& unique_translation() const {
        if (_total != 1) {
            throw std::runtime_error("attempt to fetch unique translation when _total != 1");
        }
        return _first;
    }

    int total() const {
        return _total;
    }

    int total_correct() const {
        return _total_correct;
    }

private:
    std::string _first;
    int _total_correct = 0;
    int _total = 0;
};

class Dictionary {
public:
    void ParseEntries(std::istream& in, int n) {
        std::string dutch, english, correct;
        for (int i = 0; i < n; ++i) {
            in >> dutch >> english >> correct;
            if (!in) break;
            _dictionary[dutch].AddTranslation(english, correct == "correct");
        }
    }

    const DictEntry& Get(const std::string& word) const {
        return _dictionary.at(word);
    }

private:
    std::unordered_map<std::string, DictEntry> _dictionary;
};



void solution(std::istream& in, std::ostream& out) {
    int n, m;
    std::vector<std::string> words;
    Dictionary dict;


    in >> n;
    words.resize(n);
    std::copy_n(std::istream_iterator<std::string>(in), n, words.begin());


    in >> m;
    dict.ParseEntries(in, m);

    bool isUnique = std::all_of(words.cbegin(), words.cend(), [&](const std::string& word) {
       return dict.Get(word).total() == 1;
    });
    if (isUnique) {
        bool isCorrect = std::all_of(words.cbegin(), words.cend(), [&](const std::string& word) {
            return dict.Get(word).total_correct() == 1;
        });

        for (auto it = words.begin(); it != words.end(); ++it) {
            const std::string& translation = dict.Get(*it).unique_translation();

            out << translation;
            if (std::next(it) != words.end()) {
                out << ' ';
            }
        }
        out << '\n';
        out << (isCorrect ? "correct\n" : "incorrect\n");
    } else {
        long long correct_count = 1;
        long long  total_count = 1;
        for (auto& word : words) {
            auto& entry = dict.Get(word);
            correct_count *= entry.total_correct();
            total_count *= entry.total();
        }

        out << correct_count << " correct\n";
        out << (total_count - correct_count) << " incorrect\n";
    }
}

} // namespace dunglish
