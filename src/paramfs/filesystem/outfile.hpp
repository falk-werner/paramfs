#ifndef PARAMFS_FILESYSTEM_OUTFILE_HPP
#define PARAMFS_FILESYSTEM_OUTFILE_HPP

#include "paramfs/filesystem/pseudofile_i.hpp"

#include <functional>
#include <vector>

namespace paramfs
{

constexpr size_t const outfile_default_max_capacity = (1 * 1024 * 1024);
 
using write_callback = std::function<void(char const * buffer, size_t length)>;

class outfile: public pseudofile_i
{
public:
    explicit outfile(write_callback callback, size_t max_capcity = outfile_default_max_capacity);
    ~outfile() override;
    size_t size() override;
    int read(char * buffer, size_t size, off_t offset) override;
    int write(char const * buffer, size_t size, off_t offset) override;
private:
    write_callback const callback_;
    size_t const max_capacity_;
    std::vector<char> data;

};

}

#endif
