#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "statisticians.hpp"

TEST(TestStatisticians, 2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("statisticians/samples/2.in");
        ASSERT_FALSE(in.fail());

        statisticians::solution(in, ss);
    }

    std::ifstream ans("statisticians/samples/2.ans");
    ASSERT_FALSE(ans.fail());

    int lineCount = 0;
    double got, want;
    ss >> got;
    ans >> want;

    ASSERT_FALSE(ss.fail());

    ++lineCount;
    ASSERT_NEAR(got, want, 0.001) << "line = " << lineCount;
}

TEST(TestStatisticians, 1Sample) {

    std::stringstream ss;
    {
        std::ifstream in("statisticians/samples/1.in");
        ASSERT_FALSE(in.fail());

        statisticians::solution(in, ss);
    }

    std::ifstream ans("statisticians/samples/1.ans");
    ASSERT_FALSE(ans.fail());

    int lineCount = 0;
    double got, want;
    ss >> got;
    ans >> want;

    ASSERT_FALSE(ss.fail());

    ++lineCount;
    ASSERT_NEAR(got, want, 0.001) << "line = " << lineCount;
}
