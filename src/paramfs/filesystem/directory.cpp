#include "paramfs/filesystem/directory.hpp"

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


}