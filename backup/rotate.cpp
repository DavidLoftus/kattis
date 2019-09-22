#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    int N;
    std::string s;

    while(std::cin >> N >> s)
    {
        std::reverse(s.begin(), s.end());

        for(char& c : s)
        {
            if(c == '_')
                c = 'Z'+1;
            else if(c == '.')
                c = 'Z'+2;
            c = (c - 'A' + N) % 28 + 'A';
            if(c == 'Z'+1)
                c = '_';
            else if(c == 'Z'+2)
                c = '.';

        }

        std::cout << s << std::endl;
    }

    return 0;
}
