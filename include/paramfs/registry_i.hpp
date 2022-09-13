#ifndef PARAMFS_REGISTRY_HPP
#define PARAMFS_REGISTRY_HPP

#include <string>

namespace paramfs
{

class registry_i
{
public:
    virtual ~registry_i() = default;
    virtual void add_param(std::string const &path);
};

}

#endif
