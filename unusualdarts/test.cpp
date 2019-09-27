#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "unusualdarts.hpp"

TEST(TestUnusualdarts, ASample) {

    std::stringstream ss;
    {
        std::ifstream in("unusualdarts/samples/a.in");
        ASSERT_FALSE(in.fail());

        unusualdarts::solution(in, ss);
    }

    std::ifstream ans("unusualdarts/samples/a.ans");
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
