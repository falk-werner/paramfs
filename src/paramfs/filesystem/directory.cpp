#include "paramfs/filesystem/directory.hpp"
#include "paramfs/param_error.hpp"

namespace paramfs
{

directory::directory(std::string const & name)
: name_(name)
{

}

std::string const & directory::name() const
{
    return name_;
}

int directory::mode() const
{
    return 0444;
}

bool directory::is_dir() const
{
    return true;
}

node_i * directory::get_child(std::string const & name)
{
    node_i * result = nullptr;

    auto it = child_nodes.find(name);
    if (it != child_nodes.end())
    {
        result = it->second.get();
    }

    return result;
}

void directory::iterate_child_nodes(std::function<void(node_i &)> visit)
{
    for(auto const & entry: child_nodes)
    {
        node_i * node = entry.second.get();
        visit(*node);
    }
}

void directory::add_child(std::unique_ptr<node_i> node)
{
    auto it = child_nodes.find(node->name());
    if (it == child_nodes.end())
    {
        child_nodes[node->name()] = std::move(node);
    }
    else
    {
        throw param_error(status::bad_internal_error, "path already exists");
    }
}

std::unique_ptr<pseudofile_i> directory::open_for_read()
{
    throw param_error(status::bad_internal_error, "no contents");
}

std::unique_ptr<pseudofile_i> directory::open_for_write()
{
    throw param_error(status::bad_internal_error, "no contents");
}

}