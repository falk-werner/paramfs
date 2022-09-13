#include "paramfs/status.hpp"

namespace paramfs
{

char const * to_string(status value)
{
    switch (value)
    {
        case status::good:
            return "good";
        case status::bad:
            return "bad";
        case status::bad_not_implemented:
            return "bad (not implemented)";
        case status::bad_unknown_path:
            return "bad (unknown path)";
        default:
            return "bad (unknown status code)";
    }
}

}