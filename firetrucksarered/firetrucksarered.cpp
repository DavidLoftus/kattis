#include "firetrucksarered.hpp"
#include <unordered_set>
#include <set>
#include <iterator>
#include <algorithm>
#include <vector>
#include <queue>
#include <ostream>
#include <unordered_map>


namespace firetrucksarered {

struct Person {
    std::vector<int> attributes;
};

std::istream& operator>>(std::istream& in, Person& person) {
    int m;
    in >> m;

    person.attributes.clear();
    std::copy_n(std::istream_iterator<int>(in), m, std::back_inserter(person.attributes));

    return in;
}

class Connection {
public:
    Connection(unsigned int p, unsigned int q, int attr) : p(p), q(q), attr(attr) {}

    friend std::ostream &operator<<(std::ostream& os, const Connection& connection) {
        return os << (connection.p+1) << " " << (connection.q+1) << " " << connection.attr;
    }
private:
    unsigned p, q;
    int attr;
};



void solution(std::istream& in, std::ostream& out) {

    int n;
    in >> n;

    std::vector<Person> people;

    people.reserve(n);
    std::copy_n(std::istream_iterator<Person>(in), n, std::back_inserter(people));

    std::vector<bool> visitedPeople(n);
    visitedPeople[0] = true;

    std::unordered_set<int> visitedAttributes;

    std::unordered_map<int,std::vector<unsigned>> people_with_attr;
    for (unsigned i = 1; i < people.size(); ++i) {
        for (int attr : people[i].attributes) {
            people_with_attr[attr].push_back(i);
        }
    }

    std::queue<unsigned> person_queue;

    // First person shall be in queue
    person_queue.push(0);

    std::vector<Connection> proof;

    while (!person_queue.empty()) {
        unsigned personIdx = person_queue.front();
        person_queue.pop();

        auto& person = people[personIdx];

        for (int attr : person.attributes) {
            if (visitedAttributes.count(attr) == 1) continue;
            visitedAttributes.insert(attr);
            for (unsigned i : people_with_attr[attr]) {
                if (i == personIdx || visitedPeople[i]) {
                    continue;
                }
                visitedPeople[i] = true;

                proof.emplace_back(personIdx, i, attr);
                person_queue.push(i);
            }
        }
    }

    if (!std::all_of(visitedPeople.cbegin(), visitedPeople.cend(), [](bool b){return b;})) {
        out << "impossible\n";
    } else {
        std::copy(proof.cbegin(), proof.cend(), std::ostream_iterator<Connection>(out, "\n"));
    }


}

} // namespace firetrucksarered
