#ifndef PARAMFS_FILESYSTEM_HPP
#define PARAMFS_FILESYSTEM_HPP

#include "paramfs/filesystem/directory.hpp"
#include <unordered_map>
#include <cinttypes>

namespace paramfs
{

class filesystem
{
public:
    filesystem();
    ~filesystem() = default;
    node_i * get_node(std::string const & path);
    void add(std::string const & path, std::unique_ptr<node_i> node);
    uint64_t open_file(std::string const & contents);
    std::string const& get_contents(uint64_t handle);
    void close_file(uint64_t handle);
private:
    directory root;
    uint64_t fh;
    std::unordered_map<uint64_t, std::string> open_files;
};

}

#endif
