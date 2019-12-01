#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "averagerank.hpp"

#define MAX_ERROR 0.000001
bool inBounds(double expected, double actual) {
    double delta = std::abs(expected - actual);
    return delta <= MAX_ERROR || delta/expected <= MAX_ERROR;
}

TEST(TestAveragerank, 2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("averagerank/samples/2.in");
        ASSERT_FALSE(in.fail());

        averagerank::solution(in, ss);
    }

    std::ifstream ans("averagerank/samples/2.ans");
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

TEST(TestAveragerank, 3Sample) {

    std::stringstream ss;
    {
        std::ifstream in("averagerank/samples/3.in");
        ASSERT_FALSE(in.fail());

        averagerank::solution(in, ss);
    }

    std::ifstream ans("averagerank/samples/3.ans");
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

TEST(TestAveragerank, 1Sample) {

    std::stringstream ss;
    {
        std::ifstream in("averagerank/samples/1.in");
        ASSERT_FALSE(in.fail());

        averagerank::solution(in, ss);
    }

    std::ifstream ans("averagerank/samples/1.ans");
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
