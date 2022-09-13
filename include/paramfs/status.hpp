#ifndef PARAMFS_STATUS_HPP
#define PARAMFS_STATUS_HPP

namespace paramfs
{

enum class status
{
    good = 0,
    bad,
    bad_not_implemented,
    bad_unknown_path
};

char const * to_string(status value);

}

#endif