#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "4thought.hpp"

TEST(Test4thought, 4thoughtSample) {

    std::stringstream ss;
    {
        std::ifstream in("4thought/samples/4thought.in");
        ASSERT_FALSE(in.fail());

        _4thought::solution(in, ss);
    }

    std::ifstream ans("4thought/samples/4thought.ans");
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
