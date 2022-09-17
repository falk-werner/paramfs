#include "paramfs/filesystem/filesystem.hpp"
#include "paramfs/param_error.hpp"

#include <fcntl.h>

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

int filesystem::access(std::string const & path, int mask)
{
    auto * node = get_node(path);

    if (nullptr != node)
    {
        return (0 != (mask & node->mode())) ? 0 : -EACCES;
    }
    else
    {
        return -ENOENT;
    }
}

int filesystem::readdir(std::string const & path, std::function<void(std::string const &name)> add)
{
    auto * dir = get_node(path);

    if (nullptr != dir)
    {
        if (dir->is_dir())
        {
            add(".");
            add("..");

            dir->iterate_child_nodes([&add](auto & node) {
                add(node.name());
            });

            return 0;
        }
        else
        {
            return -ENOTDIR;
        }
    }
    else
    {
        return -ENOENT;
    }

}


int filesystem::getattr(std::string const & path, struct stat * buffer, uint64_t * handle)
{
    auto * node = get_node(path);

    if (nullptr != node)
    {
        if (node->is_dir())
        {
            buffer->st_mode = S_IFDIR | node->mode();
            buffer->st_nlink = 2;
        }
        else
        {
            buffer->st_mode = S_IFREG | node->mode();
            buffer->st_nlink = 1;

            off_t size = 0;
            if (nullptr != handle)
            {
                auto it = open_files.find(*handle);
                if (it != open_files.end())
                {
                    auto & file = it->second;
                    size = file->size();
                }                
            }

            buffer->st_size = size;
        }
        return 0;
    }
    else
    {
        return -ENOENT;
    }
}




int filesystem::open(std::string const & path, int flags, uint64_t & handle)
{
    auto * const node = get_node(path);
    if (nullptr != node)
    {
        if (!node->is_dir())
        {
            int const access_mode = flags & O_ACCMODE;
            switch (access_mode)
            {
                case O_RDONLY:
                    handle = ++fh;
                    open_files[handle] = std::move(node->open_for_read());
                    return 0;
                case O_WRONLY:
                    handle = ++fh;
                    open_files[handle] = std::move(node->open_for_write());
                    return 0;
                default:
                    return -EACCES;
            }

        }
        else
        {
            return -EACCES;
        }
    }
    else
    {
        return -ENOENT;
    }

}


void filesystem::release(uint64_t handle)
{
    auto it = open_files.find(handle);
    if (it != open_files.end())
    {
        open_files.erase(it);
    }
}

int filesystem::read(uint64_t handle, char * buffer, size_t size, off_t offset)
{
    auto it = open_files.find(handle);
    if (it != open_files.end())
    {
        auto & file = it->second;
        return file->read(buffer, size, offset);
    }
    else
    {
        return -EBADF;
    }
}

int filesystem::write(uint64_t handle, char const * buffer, size_t size, off_t offset)
{
    auto it = open_files.find(handle);
    if (it != open_files.end())
    {
        auto & file = it->second;
        return file->write(buffer, size, offset);
    }
    else
    {
        return -EBADF;
    }
}


}