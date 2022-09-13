#include "paramfs/param_error.hpp"

namespace paramfs
{

param_error::param_error(status code, std::string const & reason)
: reason_(reason)
, code_(code)
{

}

char const * param_error::what() const noexcept
{
    return reason_.c_str();
}

status param_error::status_code() const
{
    return code_;
}


}