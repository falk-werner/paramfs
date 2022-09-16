#ifndef PARAMFS_FILESYSTEM_HPP
#define PARAMFS_FILESYSTEM_HPP

#include "paramfs/filesystem/directory.hpp"
#include "paramfs/filesystem/pseudofile_i.hpp"

#include <sys/stat.h>

#include <cinttypes>
#include <unordered_map>
#include <functional>

namespace paramfs
{

class filesystem
{
public:
    filesystem();
    ~filesystem() = default;
    void add(std::string const & path, std::unique_ptr<node_i> node);

    int access(std::string const & path, int mask);
    int getattr(std::string const & path, struct stat * buffer, uint64_t * handle);
    int readdir(std::string const & path, std::function<void(std::string const &name)> add);
    int open(std::string const & path, int flags, uint64_t & handle);
    void release(uint64_t handle);
    int read(uint64_t handle, char * buffer, size_t size, off_t offset);
    int write(uint64_t handle, char const * buffer, size_t size, off_t offset);
private:
    node_i * get_node(std::string const & path);
    
    directory root;
    uint64_t fh;
    std::unordered_map<uint64_t, std::unique_ptr<pseudofile_i>> open_files;
};

}

#endif
