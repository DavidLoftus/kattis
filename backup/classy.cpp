#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

bool ends_with(const std::string& str, const std::string& prefix)
{
    return std::mismatch(prefix.rbegin(), prefix.rend(), str.rbegin()).first == prefix.rend();
}

class class_tree
{
public:
    void insert(std::string name, std::string clss)
    {
        if(clss.empty())
            m_members.push_back(std::move(name));
        else if(ends_with(clss, "upper"))
        {
            int len = clss.size() - 5;
            if(len>0 && clss[len-1] == '-')
                --len;
            if(!m_upper)
                m_upper = std::make_unique<class_tree>();
            m_upper->insert(std::move(name), clss.substr(0,len));
        }
        else if(ends_with(clss, "middle"))
        {
            int len = clss.size() - 6;
            if(len>0 && clss[len-1] == '-')
                --len;
            if(!m_middle)
                m_middle = std::make_unique<class_tree>();
            m_middle->insert(std::move(name), clss.substr(0,len));
        }
        else if(ends_with(clss, "lower"))
        {
            int len = clss.size() - 5;
            if(len>0 && clss[len-1] == '-')
                --len;
            if(!m_lower)
                m_lower = std::make_unique<class_tree>();
            m_lower->insert(std::move(name), clss.substr(0,len));
        }
        else
        {
            std::cerr << "wtf? " << clss << std::endl;
        }
    }

    void dump(const std::vector<std::string>& middlenames = {})
    {
        m_members.insert(m_members.end(),middlenames.begin(), middlenames.end());
        std::sort(m_members.begin(), m_members.end());

        if(m_upper)
            m_upper->dump();

        if(m_middle)
            m_middle->dump(m_members);
        else
            for(auto& s : m_members)
            {
                std::cout << s << std::endl;
            }

        if(m_lower)
            m_lower->dump();
    }

private:
    std::unique_ptr<class_tree> m_lower, m_middle, m_upper;
    std::vector<std::string> m_members;
};

int main()
{
    int T;
    std::cin >> T;

    for(int i = 0; i < T; ++i)
    {
        int n;
        std::cin >> n;

        class_tree root;

        for(int i = 0; i < n; ++i)
        {
            std::string name, clss, ignore;
            std::cin >> name >> clss >> ignore; std::cin.ignore();
            name.pop_back(); // removes : char

            root.insert(std::move(name), std::move(clss));

        }

        root.dump();
        std::cout << "==============================" << std::endl;

    }

    return 0;
}
