#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "disgruntledjudge.hpp"

TEST(TestDisgruntledjudge, SampleSample) {

    std::stringstream ss;
    {
        std::ifstream in("disgruntledjudge/samples/sample.in");
        ASSERT_FALSE(in.fail());

        disgruntledjudge::solution(in, ss);
    }

    std::ifstream ans("disgruntledjudge/samples/sample.ans");
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
