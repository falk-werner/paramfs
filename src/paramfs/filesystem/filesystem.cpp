#include "paramfs/filesystem/filesystem.hpp"
#include "paramfs/param_error.hpp"

#include <sstream>

namespace paramfs
{

filesystem::filesystem()
: root("")
, fh(0)
{
}

node_i * filesystem::get_node(std::string const & path)
{
    node_i * current = &root;

    std::stringstream stream(path);
    std::string segment;
    while ((current != nullptr) && (std::getline(stream, segment, '/')))
    {
        if (!segment.empty())
        {
            current = current->get_child(segment);
        }
    }

    return current;
}

void filesystem::add(std::string const & path, std::unique_ptr<node_i> node)
{
    node_i * current = &root;

    std::stringstream stream(path);
    std::string segment;
    while (std::getline(stream, segment, '/'))
    {
        if (!segment.empty())
        {
            node_i * next = current->get_child(segment);
            if (nullptr == next)
            {
                auto dir = std::make_unique<directory>(segment);
                current->add_child(std::move(dir));

                next = current->get_child(segment);
            }

            current = next;
        }
    }

    current->add_child(std::move(node));
}

uint64_t filesystem::open_file(std::string const & contents)
{
    fh++;
    open_files[fh] = contents;
    return fh;
}

std::string const& filesystem::get_contents(uint64_t handle)
{
    auto it = open_files.find(handle);
    if (it != open_files.end())
    {
        return it->second;
    }
    else
    {
        throw param_error(status::bad);
    }
}

void filesystem::close_file(uint64_t handle)
{
    auto it = open_files.find(handle);
    if (it != open_files.end())
    {
        open_files.erase(it);
    }
}

}