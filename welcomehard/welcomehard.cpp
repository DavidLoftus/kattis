#include "welcomehard.hpp"

#include <string>
#include <vector>
#include <iomanip>

namespace welcomehard {

int solve(const std::string& line) {
    const std::string phrase = "welcome to code jam";

    std::vector<int> arr(line.size()+1, 1);
    for (char c : phrase) {
        int lastVal = arr[0];
        arr[0] = 0;
        for (size_t j = 1; j <= line.size(); ++j) {
            if (line[j-1] == c) {
                int arrJ = arr[j];
                arr[j] = (lastVal + arr[j-1]) % 10000;
                lastVal = arrJ;
            } else {
                lastVal = arr[j];
                arr[j] = arr[j-1];
            }
        }
    }
    return arr.back();
}

void solution(std::istream& in, std::ostream& out) {
    int n;
    in >> n; in.ignore();

    std::string line;
    for(int i = 0; i < n; ++i) {
        std::getline(in, line);

        int answer = solve(line);
        out << "Case #" << (i+1) << ": " <<
            std::setfill('0') << std::setw(4) << answer << std::endl;
    }

}

} // namespace welcomehard
