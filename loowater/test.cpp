#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "loowater.hpp"

TEST(TestLoowater, CSample) {

    std::stringstream ss;
    {
        std::ifstream in("loowater/samples/C.in");
        ASSERT_FALSE(in.fail());

        loowater::solution(in, ss);
    }

    std::ifstream ans("loowater/samples/C.ans");
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
