#include "paramfs/status.hpp"
#include <gtest/gtest.h>

using paramfs::to_string;
using paramfs::status;

namespace
{

struct param
{
    std::string expected;
    status code;
};

class status_test_fixture: public ::testing::TestWithParam<param> { };

}

TEST_P(status_test_fixture, to_string)
{
    auto const & p = GetParam();
    ASSERT_EQ(p.expected, paramfs::to_string(p.code));
}

INSTANTIATE_TEST_CASE_P(status_test, status_test_fixture, ::testing::Values(
    param{"good", status::good},
    param{"bad", status::bad},
    param{"bad (internal error)", status::bad_internal_error},
    param{"bad (not implemented)", status::bad_not_implemented},
    param{"bad (unknown path)", status::bad_unknown_path},
    param{"bad (paramter already provided)", status::bad_parameter_already_provided}
));

TEST(status, to_string_unknown_code)
{
    ASSERT_STREQ("bad (unknown status code)", paramfs::to_string(static_cast<status>(-42)));
}
