#ifndef PARAMFS_INFILE_HPP
#define PARAMFS_INFILE_HPP

#include "paramfs/filesystem/pseudofile_i.hpp"
#include <string>

namespace paramfs
{

class infile: public pseudofile_i
{
public:
    explicit infile(std::string const& contents);
    ~infile() override = default;
    size_t size() override;
    int read(char * buffer, size_t size, off_t offset) override;
    int write(char const * buffer, size_t size, off_t offset) override;
public:
    std::string const contents_;
};

}

#endif
