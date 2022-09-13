#ifndef PARAMFS_FILESYSTEM_DIRECTORY_H
#define PARAMFS_FILESYSTEM_DIRECTORY_H

#include "paramfs/filesystem/node_i.hpp"
#include <unordered_map>
#include <memory>

namespace paramfs
{

class directory: public node_i
{
public:
    directory(std::string const & name);
    ~directory() override = default;
    std::string const & name() const override;
    int mode() const override;
    bool is_dir() const override;
    node_i * get_child(std::string const & name) override;
    void iterate_child_nodes(std::function<void(node_i &)> visit) override;
private:
    std::string name_;
    std::unordered_map<std::string, std::unique_ptr<node_i>> child_nodes;
};

}

#endif