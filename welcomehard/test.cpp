#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "welcomehard.hpp"

TEST(TestWelcomehard, SampleSample) {

    std::stringstream ss;
    {
        std::ifstream in("welcomehard/samples/sample.in");
        ASSERT_FALSE(in.fail());

        welcomehard::solution(in, ss);
    }

    std::ifstream ans("welcomehard/samples/sample.ans");
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
