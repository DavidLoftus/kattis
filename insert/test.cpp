#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "insert.hpp"

TEST(TestInsert, InsertSample) {

    std::stringstream ss;
    {
        std::ifstream in("insert/samples/insert.in");
        ASSERT_FALSE(in.fail());

        insert::solution(in, ss);
    }

    std::ifstream ans("insert/samples/insert.ans");
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
