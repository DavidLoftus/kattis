#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "glyphrecognition.hpp"

TEST(TestGlyphrecognition, 2Sample) {

    std::stringstream ss;
    {
        std::ifstream in("glyphrecognition/samples/2.in");
        ASSERT_FALSE(in.fail());

        glyphrecognition::solution(in, ss);
    }

    std::ifstream ans("glyphrecognition/samples/2.ans");
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

TEST(TestGlyphrecognition, 1Sample) {

    std::stringstream ss;
    {
        std::ifstream in("glyphrecognition/samples/1.in");
        ASSERT_FALSE(in.fail());

        glyphrecognition::solution(in, ss);
    }

    std::ifstream ans("glyphrecognition/samples/1.ans");
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
