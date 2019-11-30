#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "gnollhypothesis.hpp"

#define MAX_ERROR 0.000001
bool inBounds(double expected, double actual) {
    double delta = std::abs(expected - actual);
    return delta <= MAX_ERROR || delta/expected <= MAX_ERROR;
}

TEST(TestGnollhypothesis, 1Sample) {

    std::stringstream ss;
    {
        std::ifstream in("gnollhypothesis/samples/1.in");
        ASSERT_FALSE(in.fail());

        gnollhypothesis::solution(in, ss);
    }

    std::ifstream ans("gnollhypothesis/samples/1.ans");
    ASSERT_FALSE(ans.fail());

    int i = 0;
    double got, want;

    for (;;) {
        ss >> got;
        ans >> want;
        if(ss.fail() && ans.fail()) {
            break;
        }

        ASSERT_TRUE(inBounds(want, got)) << "want = " << want << " got = " << got << " i = " << i;
        ++i;
    }
}

TEST(TestGnollhypothesis, 2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("gnollhypothesis/samples/2.in");
        ASSERT_FALSE(in.fail());

        gnollhypothesis::solution(in, ss);
    }

    std::ifstream ans("gnollhypothesis/samples/2.ans");
    ASSERT_FALSE(ans.fail());

    int i = 0;
    double got, want;

    for (;;) {
        ss >> got;
        ans >> want;
        if(ss.fail() && ans.fail()) {
            break;
        }

        ASSERT_TRUE(inBounds(want, got)) << "want = " << want << " got = " << got << " i = " << i;
        ++i;
    }
}
