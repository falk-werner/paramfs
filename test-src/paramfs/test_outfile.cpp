#include "paramfs/filesystem/outfile.hpp"
#include <gtest/gtest.h>

using paramfs::outfile;

TEST(outfile, write)
{
    std::string expected = "42";
    std::string actual;

    {
        outfile out([&actual](char const * data, size_t length) {
            actual = std::string(data, length);
        });
        out.write(expected.c_str(), expected.size(), 0);
    }

    ASSERT_EQ(actual, expected);
}