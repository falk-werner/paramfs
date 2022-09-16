#include "paramfs/filesystem/outfile.hpp"

#include <errno.h>
#include <cstring>

namespace paramfs
{

outfile::outfile(write_callback callback, size_t max_capacity)
: callback_(callback)
, max_capacity_(max_capacity)
{

}

outfile::~outfile()
{
    callback_(data.data(), data.size());
}

size_t outfile::size()
{
    return data.size();
}

int outfile::read(char * buffer, size_t size, off_t offset)
{
    return -EACCES;
}

int outfile::write(char const * buffer, size_t size, off_t offset)
{
    size_t const needed = offset + size;
    if (needed > max_capacity_)
    {
        return -EFAULT;
    }

    if (needed > data.capacity())
    {
        size_t const capacity = ((2 * needed) < max_capacity_) ? (2 * needed) : max_capacity_;        
        data.reserve(capacity);
    }

    void const * from = reinterpret_cast<void const *>(buffer);
    void * to = reinterpret_cast<void*>(&data.data()[offset]);

    memcpy(to, from, size);
    return size;
}


}