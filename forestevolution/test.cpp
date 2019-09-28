#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "forestevolution.hpp"

TEST(TestForestevolution, 02Sample) {

    std::stringstream ss;
    {
        std::ifstream in("forestevolution/samples/02.in");
        ASSERT_FALSE(in.fail());

        forestevolution::solution(in, ss);
    }

    std::ifstream ans("forestevolution/samples/02.ans");
    ASSERT_FALSE(ans.fail());

    int lineCount = 0;
    double got, want;

    for (;;) {
        ss >> got;
        ans >> want;
        if(ss.fail() && ans.fail()) {
            break;
        }

        ++lineCount;
        ASSERT_NEAR(got, want, 0.001) << "line = " << lineCount;
    }
}

TEST(TestForestevolution, 01Sample) {

    std::stringstream ss;
    {
        std::ifstream in("forestevolution/samples/01.in");
        ASSERT_FALSE(in.fail());

        forestevolution::solution(in, ss);
    }

    std::ifstream ans("forestevolution/samples/01.ans");
    ASSERT_FALSE(ans.fail());

    int lineCount = 0;
    double got, want;

    for (;;) {
        ss >> got;
        ans >> want;
        if(ss.fail() && ans.fail()) {
            break;
        }

        ++lineCount;
        ASSERT_NEAR(got, want, 0.001) << "line = " << lineCount;
    }
}
