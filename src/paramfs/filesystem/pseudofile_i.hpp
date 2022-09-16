#ifndef PARAMFS_PSEUDOFILE_I_HPP
#define PARAMFS_PSEUDOFILE_I_HPP

#include <cstddef>
#include <sys/types.h>

namespace paramfs
{

class pseudofile_i
{
public:
    virtual ~pseudofile_i() = default;
    virtual size_t size() = 0;
    virtual int read(char * buffer, size_t size, off_t offset) = 0;
    virtual int write(char const * buffer, size_t size, off_t offset) = 0;
};

}

#endif
