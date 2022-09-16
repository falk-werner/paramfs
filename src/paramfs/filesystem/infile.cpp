#include "paramfs/filesystem/infile.hpp"
#include <cstring>

namespace paramfs
{

infile::infile(std::string const& contents)
: contents_(contents)
{

}

size_t infile::size()
{
    return contents_.size();
}

int infile::read(char * buffer, size_t size, off_t offset)
{
    size_t const file_size = this->size();
    if (file_size > offset)
    {
        size_t const remaining = file_size - offset;
        size_t const length = (size < remaining) ? size : remaining;

        void * const to = reinterpret_cast<void*>(buffer);
        void const * const from = reinterpret_cast<void const*>(&contents_.c_str()[offset]);

        memcpy(to, from, length);
        return length;
    }
    else if (file_size == offset)
    {
        return 0;
    }
    else
    {
        return -EFAULT;
    }
}

int infile::write(char const * buffer, size_t size, off_t offset)
{
    (void) buffer;
    (void) size;
    (void) offset;

    return -EACCES;
}


}