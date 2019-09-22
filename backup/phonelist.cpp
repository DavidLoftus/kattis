#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_set>

bool check_collision(const std::vector<std::string>& numbers)
{
    std::array<std::unordered_set<std::string>,10> prefixes;

    for(auto& num : numbers)
    {
        prefixes[num.size()-1].insert(num);
    }

    for(auto& num : numbers)
    {
        for(size_t i = 0; i < num.size()-1; ++i)
        {
            if(prefixes[i].count(num.substr(0,i+1)) != 0)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int t;
    std::cin >> t;

    for(int i = 0; i < t; ++i)
    {
        int n;
        std::cin >> n;
        std::vector<std::string> numbers;
        numbers.reserve(n);


        std::copy_n(std::istream_iterator<std::string>(std::cin), n, std::back_inserter(numbers));
        //std::sort(numbers.begin(), numbers.end(), [](auto& a, auto& b){ return a.size() < b.size(); });
        std::cout << (check_collision(numbers) ? "NO" : "YES") << std::endl;
    }

    return 0;
}
