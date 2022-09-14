#ifndef PARAMFS_FILESYSTEM_NODE_I_HPP
#define PARAMFS_FILESYSTEM_NODE_I_HPP

#include <string>
#include <functional>
#include <memory>

namespace paramfs
{

class node_i
{
public:
    virtual ~node_i() = default;
    virtual std::string const & name() const = 0;
    virtual int mode() const = 0;
    virtual bool is_dir() const = 0;
    virtual node_i * get_child(std::string const & name) = 0;
    virtual void iterate_child_nodes(std::function<void(node_i &)> visit) = 0;
    virtual void add_child(std::unique_ptr<node_i> node) = 0;
    virtual std::string get_contents() = 0;
};

}

#endif
