#include "dyslectionary.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using std::string;

namespace dyslectionary {

void solution(std::istream& in, std::ostream& out) {

    while (in) {
        std::vector<string> words;

        string word;
        while (true) {
            std::getline(in, word);
            if (word.empty()) {
                break;
            }
            words.push_back(std::move(word));
        }

        for(string& word : words) {
            std::reverse(word.begin(), word.end());
        }
        std::sort(words.begin(), words.end()/*, reverseCompare*/);
        for(string& word : words) {
            std::reverse(word.begin(), word.end());
        }

        // Set padding size to maximum size
        auto it = std::max_element(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });
        size_t padSz = it->size();

        for (const string& word : words) {
            out << std::setw(padSz) <<  word << '\n';
        }
        out << '\n';
    }

}

} // namespace dyslectionary
