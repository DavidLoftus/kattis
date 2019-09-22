#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>
#include <limits>
#include <math.h>
#include <iomanip>

struct station_t
{
    int x, y;

    int distance(station_t other) const
    {
        int dx = x-other.x, dy = y-other.y;
        return dx*dx+dy*dy;
    }
};

struct network_t
{
    std::list<station_t> stations;
    int D = 0;

    int distance(station_t other) const
    {
        int minDist = std::numeric_limits<int>::max();
        //std::cout << "distance from network: " << this << std::endl;
        for(auto& station : stations)
        {
            //std::cout << &station << std::endl;
            int dist = station.distance(other);
            if(dist < minDist)
            {
                minDist = dist;
            }
        }
        return minDist;
    }

    int distance(const network_t& other) const
    {
        int minDist = std::numeric_limits<int>::max();

        //std::cout << "network " << this << " from network: " << &other << std::endl;
        for(auto& station : other.stations)
        {
            int dist = distance(station);
            if(dist < minDist)
            {
                minDist = dist;
            }
        }
        return minDist;
    }

    void digest(network_t& other, int dist)
    {
        stations.splice(stations.begin(),other.stations);
        D = std::max(dist,std::max(D,other.D));
    }
};

int main()
{
    int N;
    std::cin >> N;

    for(int i = 0; i < N; ++i)
    {
        int S, P;
        std::cin >> S >> P;

        std::list<network_t> networks;

        for(int i = 0; i < P; ++i)
        {
            station_t station;
            std::cin >> station.x >> station.y;
            networks.emplace_back();
            networks.back().stations.push_back(station);
            //std::cout << i << ": " << &networks.back() << std::endl;
        }

        using iter_t = typename std::list<network_t>::iterator;
        while(networks.size() > S)
        {
            int minDist = std::numeric_limits<int>::max();
            iter_t itA, itB;

            for(auto it = networks.begin(); it != networks.end(); ++it)
            {
                for(auto it2 = std::next(it); it2 != networks.end(); ++it2)
                {
                    int dist = it->distance(*it2);
                    if(dist < minDist)
                    {
                        minDist = dist;
                        itA = it, itB = it2;
                    }
                }
            }

            itA->digest(*itB, minDist);
            networks.erase(itB);
        }

        auto it = std::max_element(networks.begin(), networks.end(), [](auto& a, auto& b){ return a.D < b.D; });
        std::cout << std::fixed << std::setprecision(2) << std::sqrt(it->D) << std::endl;
    }

    return 0;
}
