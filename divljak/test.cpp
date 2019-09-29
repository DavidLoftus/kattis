#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "divljak.hpp"

TEST(TestDivljak, Divljak_1Sample) {

    std::stringstream ss;
    {
        std::ifstream in("divljak/samples/divljak.1.in");
        ASSERT_FALSE(in.fail());

        divljak::solution(in, ss);
    }

    std::ifstream ans("divljak/samples/divljak.1.ans");
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

TEST(TestDivljak, Divljak_2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("divljak/samples/divljak.2.in");
        ASSERT_FALSE(in.fail());

        divljak::solution(in, ss);
    }

    std::ifstream ans("divljak/samples/divljak.2.ans");
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
