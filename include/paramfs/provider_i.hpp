#ifndef PARAMFS_PROVIDER_I_HPP
#define PARAMFS_PROVIDER_I_HPP

#include <string>

namespace paramfs
{

class registry_i;

class provider_i
{
public:
    virtual ~provider_i() = default;
    virtual std::string const & name() const = 0;
    virtual void describe(registry_i & registry) = 0; 
    virtual std::string read(std::string const & path) = 0;
    virtual void write(std::string const & path, std::string const & value) = 0;
    virtual std::string execute(std::string const & path, std::string const & args) = 0;
};

}


#endif
