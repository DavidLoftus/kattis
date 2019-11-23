#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "firetrucksarered.hpp"

TEST(TestFiretrucksarered, 2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("firetrucksarered/samples/2.in");
        ASSERT_FALSE(in.fail());

        firetrucksarered::solution(in, ss);
    }

    std::ifstream ans("firetrucksarered/samples/2.ans");
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

TEST(TestFiretrucksarered, 1Sample) {

    std::stringstream ss;
    {
        std::ifstream in("firetrucksarered/samples/1.in");
        ASSERT_FALSE(in.fail());

        firetrucksarered::solution(in, ss);
    }

    std::ifstream ans("firetrucksarered/samples/1.ans");
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
