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

    int k_got, k_want;
    double score_got, score_want;
    ASSERT_TRUE(ss >> k_got >> score_got);

    ans >> k_want >> score_want;

    ASSERT_EQ(k_got, k_want);
    ASSERT_NEAR(score_got, score_want, 0.000001);
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

    int k_got, k_want;
    double score_got, score_want;
    ASSERT_TRUE(ss >> k_got >> score_got);

    ans >> k_want >> score_want;

    ASSERT_EQ(k_got, k_want);
    ASSERT_NEAR(score_got, score_want, 0.000001);
}
