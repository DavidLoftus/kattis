#include <utility>

#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>
#include <ostream>

#include "canvasline.hpp"

struct Canvas {
    int left;
    int right;
};

std::istream& operator>>(std::istream& is, Canvas& c){
    return is >> c.left >> c.right;
}

class Output {
public:
    Output() = default;

    bool isImpossible() const {
        return _impossible;
    };

    int numPegs() const {
        return _newPegs.size();
    }

private:
    std::vector<int> _newPegs;
    bool _impossible = false;

    friend class TestCase;
    friend std::istream& operator>>(std::istream& is, Output& output) {
        std::string s;

        if(std::getline(is, s)) {
            if (s == "impossible") {
                output._impossible = true;
                output._newPegs.clear();
            } else {
                output._impossible = false;

                int p = std::stoi(s);

                output._newPegs.resize(p);
                std::copy_n(std::istream_iterator<int>(is), p, output._newPegs.begin());

            }
        }

        return is;
    }
};


class TestCase {
public:

    void assertValid(const Output& output) {

        if (output._impossible) return;

        // Assert that new pegs don't already exist.
        for (int p : output._newPegs) {
            ASSERT_EQ(_pegs.count(p), 0) << "peg " << p << " already exists";
        }

        // Make a copy of the set for modification
        auto pegsCopy = _pegs;

        // Insert all new pegs into copy
        pegsCopy.insert(output._newPegs.cbegin(), output._newPegs.end());

        // Size should've increased by newPegs.size()
        ASSERT_EQ(pegsCopy.size(), _pegs.size() + output._newPegs.size())
            << " incorrect size of set, likely due to duplicates in output.";

        int i = 0;
        for (auto& canvas : _canvases) {
            auto leftIt = pegsCopy.lower_bound(canvas.left);
            auto rightIt = pegsCopy.upper_bound(canvas.right);
            auto n = std::distance(leftIt, rightIt);
            ++i;

            ASSERT_EQ(n, 2) << " canvas #" << i;
        }
    }
private:
    std::vector<Canvas> _canvases;
    std::set<int> _pegs;


    friend std::istream& operator>>(std::istream& is, TestCase& testCase) {
        int n;
        is >> n;

        testCase._canvases.resize(n);
        std::copy_n(std::istream_iterator<Canvas>(is), n, testCase._canvases.begin());

        int p;
        is >> p;

        testCase._pegs.clear();
        std::copy_n(std::istream_iterator<int>(is), p, std::inserter(testCase._pegs, testCase._pegs.begin()));

        return is;
    }
};

TEST(TestCanvasline, 2Sample) {

    std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

    std::stringstream ss;
    TestCase testCase;
    {
        std::ifstream in("canvasline/samples/2.in");
        ASSERT_FALSE(in.fail());

        // Read input into testcase for validation checking
        ASSERT_TRUE(in >> testCase);

        // Reset cursor
        in.seekg(0);
        canvasline::solution(in, ss);
    }

    std::ifstream ans("canvasline/samples/2.ans");
    ASSERT_FALSE(ans.fail());

    Output sampleOutput;

    int len = ans.seekg(0, std::ios_base::end).tellg();
    ans.seekg(0);

    ASSERT_TRUE(ans >> sampleOutput) << "len = " << len;
    {
        SCOPED_TRACE("Assert validity of sample output for " + testName );
        testCase.assertValid(sampleOutput);
    }

    Output output;

    // Reset reading cursor to start of stream
    ss.seekg(0);
    ASSERT_TRUE(ss >> output);
    {
        SCOPED_TRACE("Assert validity of actual output for " + testName);
        testCase.assertValid(output);
    }

    ASSERT_EQ(sampleOutput.isImpossible(), output.isImpossible());
}

TEST(TestCanvasline, 3Sample) {

    std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

    std::stringstream ss;
    TestCase testCase;
    {
        std::ifstream in("canvasline/samples/3.in");
        ASSERT_FALSE(in.fail());

        // Read input into testcase for validation checking
        ASSERT_TRUE(in >> testCase);

        // Reset cursor
        in.seekg(0);
        canvasline::solution(in, ss);
    }

    std::ifstream ans("canvasline/samples/3.ans");
    ASSERT_FALSE(ans.fail());

    Output sampleOutput;

    ASSERT_TRUE(ans >> sampleOutput);
    {
        SCOPED_TRACE("Assert validity of sample output for " + testName );
        testCase.assertValid(sampleOutput);
    }

    Output output;

    // Reset reading cursor to start of stream
    ss.seekg(0);
    ASSERT_TRUE(ss >> output);
    {
        SCOPED_TRACE("Assert validity of actual output for " + testName);
        testCase.assertValid(output);
    }

    ASSERT_EQ(sampleOutput.isImpossible(), output.isImpossible());
}

TEST(TestCanvasline, 1Sample) {

    std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

    std::stringstream ss;
    TestCase testCase;
    {
        std::ifstream in("canvasline/samples/1.in");
        ASSERT_FALSE(in.fail());

        // Read input into testcase for validation checking
        ASSERT_TRUE(in >> testCase);

        // Reset cursor
        in.seekg(0);
        canvasline::solution(in, ss);
    }

    std::ifstream ans("canvasline/samples/1.ans");
    ASSERT_FALSE(ans.fail());

    Output sampleOutput;

    ASSERT_TRUE(ans >> sampleOutput);
    {
        SCOPED_TRACE("Assert validity of sample output for " + testName );
        testCase.assertValid(sampleOutput);
    }

    Output output;

    // Reset reading cursor to start of stream
    ss.seekg(0);
    ASSERT_TRUE(ss >> output);
    {
        SCOPED_TRACE("Assert validity of actual output for " + testName);
        testCase.assertValid(output);
    }

    ASSERT_EQ(sampleOutput.isImpossible(), output.isImpossible());
    ASSERT_EQ(sampleOutput.numPegs(), output.numPegs());
}
