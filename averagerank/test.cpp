#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "averagerank.hpp"

TEST(TestAveragerank, 2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("averagerank/samples/2.in");
        ASSERT_FALSE(in.fail());

        averagerank::solution(in, ss);
    }

    std::ifstream ans("averagerank/samples/2.ans");
    ASSERT_FALSE(ans.fail());

    int lineCount = 0;
    std::string got, want;

    for (;;) {
        std::getline(ss, got);
        std::getline(ans, want);
        if(ss.fail() && ans.fail()) {
            break;
        }

        ++lineCount;
        ASSERT_EQ(got, want) << "line = " << lineCount;
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

    int lineCount = 0;
    std::string got, want;

    for (;;) {
        std::getline(ss, got);
        std::getline(ans, want);
        if(ss.fail() && ans.fail()) {
            break;
        }

        ++lineCount;
        ASSERT_EQ(got, want) << "line = " << lineCount;
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

    int lineCount = 0;
    std::string got, want;

    for (;;) {
        std::getline(ss, got);
        std::getline(ans, want);
        if(ss.fail() && ans.fail()) {
            break;
        }

        ++lineCount;
        ASSERT_EQ(got, want) << "line = " << lineCount;
    }
}
