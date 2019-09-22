#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "candydivision.hpp"

TEST(TestCandydivision, 00_sampleSample) {

    std::stringstream ss;
    {
        std::ifstream in("candydivision/samples/00.sample.in");
        ASSERT_FALSE(in.fail());

        candydivision::solution(in, ss);
    }

    std::ifstream ans("candydivision/samples/00.sample.ans");
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
