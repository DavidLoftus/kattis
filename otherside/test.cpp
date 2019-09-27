#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "otherside.hpp"

TEST(TestOtherside, 2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("otherside/samples/2.in");
        ASSERT_FALSE(in.fail());

        otherside::solution(in, ss);
    }

    std::ifstream ans("otherside/samples/2.ans");
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

TEST(TestOtherside, 1Sample) {

    std::stringstream ss;
    {
        std::ifstream in("otherside/samples/1.in");
        ASSERT_FALSE(in.fail());

        otherside::solution(in, ss);
    }

    std::ifstream ans("otherside/samples/1.ans");
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
