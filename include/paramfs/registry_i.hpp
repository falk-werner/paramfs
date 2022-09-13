#ifndef PARAMFS_REGISTRY_I_HPP
#define PARAMFS_REGISTRY_I_HPP

#include <string>

namespace paramfs
{

class registry_i
{
public:
    virtual ~registry_i() = default;
    virtual void add_param(std::string const &path) = 0;
};

}

#endif
