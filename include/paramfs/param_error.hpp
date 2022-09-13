#ifndef PARAMFS_PARAM_ERROR_HPP
#define PARAMFS_PARAM_ERROR_HPP

#include <paramfs/status.hpp>
#include <string>

namespace paramfs
{

class param_error: public std::exception
{
public:
    param_error(status code = status::bad, std::string const & reason = "");
    ~param_error() override = default;
    char const * what() const noexcept override;
    status status_code() const;
private:
    std::string reason_;
    status code_;
};

}


#endif
