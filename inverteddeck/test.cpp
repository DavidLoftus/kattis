#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "inverteddeck.hpp"

TEST(TestInverteddeck, 2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("inverteddeck/samples/2.in");
        ASSERT_FALSE(in.fail());

        inverteddeck::solution(in, ss);
    }

    std::ifstream ans("inverteddeck/samples/2.ans");
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

TEST(TestInverteddeck, 3Sample) {

    std::stringstream ss;
    {
        std::ifstream in("inverteddeck/samples/3.in");
        ASSERT_FALSE(in.fail());

        inverteddeck::solution(in, ss);
    }

    std::ifstream ans("inverteddeck/samples/3.ans");
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

TEST(TestInverteddeck, 1Sample) {

    std::stringstream ss;
    {
        std::ifstream in("inverteddeck/samples/1.in");
        ASSERT_FALSE(in.fail());

        inverteddeck::solution(in, ss);
    }

    std::ifstream ans("inverteddeck/samples/1.ans");
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
