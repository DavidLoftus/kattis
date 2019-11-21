#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "canvasline.hpp"

TEST(TestCanvasline, 2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("canvasline/samples/2.in");
        ASSERT_FALSE(in.fail());

        canvasline::solution(in, ss);
    }

    std::ifstream ans("canvasline/samples/2.ans");
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

TEST(TestCanvasline, 3Sample) {

    std::stringstream ss;
    {
        std::ifstream in("canvasline/samples/3.in");
        ASSERT_FALSE(in.fail());

        canvasline::solution(in, ss);
    }

    std::ifstream ans("canvasline/samples/3.ans");
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

TEST(TestCanvasline, 1Sample) {

    std::stringstream ss;
    {
        std::ifstream in("canvasline/samples/1.in");
        ASSERT_FALSE(in.fail());

        canvasline::solution(in, ss);
    }

    std::ifstream ans("canvasline/samples/1.ans");
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
