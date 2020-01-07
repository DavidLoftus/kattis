#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <unordered_set>
#include <iomanip>
#include "averagerank.hpp"

namespace averagerank {

struct Player {
    int oldRank = 1;
    int rank = 1;
    long long rankSum = 0;
    int points = 0;
    int week = 0;
};

class Scoreboard {
public:
    explicit Scoreboard(int n) : players(n), rankings(n) {
        std::iota(rankings.begin(), rankings.end(), 0);
    }

    void setWeek(int week) {
        currentWeek = week;
    }

    int getRank(int id) const {
        auto it = std::upper_bound(
                rankings.begin(),
                rankings.end(),
                id-1,
                [&](int a, int b){
                    return players[a].points < players[b].points;
                });
        ptrdiff_t dist = std::distance(it, rankings.end());
        return 1 + static_cast<int>(dist);
    }

    int getPoints(int id) const {
        return players[id-1].points;
    }

    double getAverageRank(int id, int week) {
        Player& player = players[id-1];
        int weekDelta = week - player.week;

        if (weekDelta > 0) {
            player.rankSum += getRank(id) * weekDelta;
        }
        return static_cast<double>(player.rankSum) / week;
    }

    template<typename It>
    void givePointsToPlayers(It start, It end, int pointsHint) {
        // Handle empty range edgecase so we can use first element.
        if (start == end) {
            return;
        }

        int idx = *start - 1;

        // Find all players with same points as player #idx
        auto rankRange = std::equal_range(
                rankings.begin(),
                rankings.end(),
                idx,
                [&](int a, int b){
                    return players[a].points < players[b].points;
                });

        int rank = std::distance(rankRange.second, rankings.end());

        int points = players[idx].points;

        // Give each player in [start, end) points
        std::for_each(start, end, [&](int i) {
            players[i-1].points++;
        });

        // Now partition this range based on points.
        // [start, end) shall now be at end of the range
        auto newRankEnd = std::partition(rankRange.first, rankRange.second, [&](int a) {
           return players[a].points == points;
        });

        // need to recalculate rank for original rank group
        std::for_each(rankRange.first, newRankEnd, [&](int a) {
            updateRank(a, rank + std::distance(start, end));
        });

        // If new points equals pointsHint then the new group will be updated too next iteration.
        // Otherwise we need to update it ourselves.
        if (points + 1 < pointsHint) {
            std::for_each(newRankEnd, rankRange.second, [&](int a) {
                updateRank(a);
            });
        }
    }

private:

    void updateRank(int i) {
        updateRank(i, getRank(i+1));
    }

    void updateRank(int i, int newRank) {
        Player& player = players[i];

        int weekDelta = currentWeek - player.week;
        if (weekDelta <= 0) {
            throw std::runtime_error("fuck wasn't expecting this");
        }

        int weeksSkipped = weekDelta - 1;
        if (weeksSkipped >= 0) {
            player.rankSum += player.oldRank * weeksSkipped;
        }
        player.rankSum += newRank;

        player.oldRank = newRank;
        player.week = currentWeek;
    }

    std::vector<Player> players;
    std::vector<int> rankings;
    int currentWeek = 0;
};

void solution(std::istream& in, std::ostream& out) {
    int n, w;
    in >> n >> w;

    Scoreboard scoreboard{n};

    for (int i = 1; i <= w; ++i) {
        int k;
        in >> k;

        scoreboard.setWeek(i);

        if (k == 0) continue;

        std::vector<int> newPoints;
        newPoints.reserve(k);
        std::copy_n(std::istream_iterator<int>(in), k, std::back_inserter(newPoints));

        std::sort(newPoints.begin(), newPoints.end(), [&](int a, int b) {
            int rankA = scoreboard.getPoints(a), rankB = scoreboard.getPoints(b);
            if (rankA == rankB) return a < b;
            return rankA < rankB;
        });

        if (i % 100 == 0) {
            std::cerr << "i = " << i << "/" << w << " #newPoints = " << newPoints.size() << "\n";
        }

        for (auto it = newPoints.begin(); it != newPoints.end();) {
            int points = scoreboard.getPoints(*it);
            auto itEnd = std::find_if_not(it, newPoints.end(), [&](int i) {
                return scoreboard.getPoints(i) == points;
            });

            int hint = std::numeric_limits<int>::max();
            if (itEnd != newPoints.end()) {
                hint = scoreboard.getPoints(*itEnd);
            }

            scoreboard.givePointsToPlayers(it, itEnd, hint);

            it = itEnd;
        }
    }

    out << std::setprecision(7);
    for (int i = 1; i <= n; ++i) {
        out << scoreboard.getAverageRank(i, w) << "\n";
    }

}

} // namespace averagerank
