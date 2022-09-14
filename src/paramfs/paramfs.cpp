#include "paramfs/paramfs.hpp"
#include "paramfs/detail.hpp"
#include "paramfs/filesystem/static_file.hpp"

#define FUSE_USE_VERSION 31
#include <fuse.h>

#include <errno.h>
#include <sys/stat.h>

#include <cstring>
#include <iostream>
namespace
{

paramfs::filesystem * get_filesystem()
{
    auto * context = fuse_get_context();
    return reinterpret_cast<paramfs::filesystem*>(context->private_data);
}

void * fs_init(fuse_conn_info * connection, fuse_config * config)
{
    (void) connection;

    config->use_ino = 1;
    config->entry_timeout = 0;
    config->attr_timeout = 0;
    config->negative_timeout = 0;

    return fuse_get_context()->private_data;
}

int fs_access(char const * path, int mask)
{
    auto * filesystem = get_filesystem();
    auto * node = filesystem->get_node(path);

    if (nullptr != node)
    {
        return (0 != (mask & node->mode())) ? 0 : -EACCES;
    }
    else
    {
        return -ENOENT;
    }
}

int fs_getattr(char const * path, struct stat * buffer, fuse_file_info * fi)
{
    auto * filesystem = get_filesystem();
    auto * node = filesystem->get_node(path);

    if (nullptr != node)
    {
        if (node->is_dir())
        {
            buffer->st_mode = S_IFDIR | node->mode();
            buffer->st_nlink = 2;
            return 0;
        }
        else
        {
            buffer->st_mode = S_IFREG | node->mode();
            buffer->st_nlink = 1;

            off_t size = 0;
            if (nullptr != fi)
            {
                try
                {
                    auto const & contents = filesystem->get_contents(fi->fh);
                    size = contents.size();
                }
                catch(...)
                {
                    // swallow
                }
                
            }

            buffer->st_size = size;
            return 0;
        }
    }
    else
    {
        return -ENOENT;
    }
}

int fs_readdir(char const * path, void * buffer, fuse_fill_dir_t filler, off_t offset, fuse_file_info * fi, fuse_readdir_flags flags)
{
    auto * filesystem = get_filesystem();
    auto * dir = filesystem->get_node(path);

    if (nullptr != dir)
    {
        if (dir->is_dir())
        {
            filler(buffer, ".", nullptr, 0, static_cast<fuse_fill_dir_flags>(0));
            filler(buffer, "..", nullptr, 0, static_cast<fuse_fill_dir_flags>(0));

            dir->iterate_child_nodes([&filler, buffer](auto & node) {
                filler(buffer, node.name().c_str(), nullptr, 0, static_cast<fuse_fill_dir_flags>(0));
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

int fs_open(char const * path, fuse_file_info * fi)
{
    auto * filesystem = get_filesystem();
    auto * file = filesystem->get_node(path);

    if (nullptr != file)
    {
        if (!file->is_dir())
        {
            fi->fh = filesystem->open_file(file->get_contents());
            return 0;
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

    return -1;
}

int fs_release(char const * path, fuse_file_info * fi)
{
    auto * filesystem = get_filesystem();
    filesystem->close_file(fi->fh);

    return 0;
}

int fs_read(char const * path, char * buffer, size_t size, off_t offset, fuse_file_info * fi)
{
    (void) path;

    auto * filesystem = get_filesystem();

    try
    {
        std::string const & contents = filesystem->get_contents(fi->fh);
        if (contents.size() > offset)
        {
            size_t const remaining = contents.size() - offset;
            size_t const len = (size < remaining) ? size : remaining;
            memcpy(reinterpret_cast<void*>(buffer), reinterpret_cast<void const*>(&contents.c_str()[offset]), len);
            return len;
        }
        else if (contents.size() == offset)
        {
            return 0;
        }
        else
        {
            return -EFAULT;
        }
    }
    catch (...)
    {
        return -EBADF;
    }
}


}

namespace paramfs
{

paramfs::paramfs()
: d(new detail)
{
}

paramfs::~paramfs()
{
    delete d;
}

int paramfs::run(int argc, char* argv[])
{
    fuse_operations ops = { 0 };
    ops.init = fs_init;
    ops.access = fs_access;
    ops.getattr = fs_getattr;
    ops.readdir = fs_readdir;
    ops.open = fs_open;
    ops.release = fs_release;
    ops.read = fs_read;

    void * filesystem = reinterpret_cast<void*>(&d->filesystem_);
    return fuse_main(argc, argv, &ops, filesystem);
}

void paramfs::add(std::shared_ptr<provider_i> provider)
{
    d->registry_.set_active_provider(provider);
    provider->describe(d->registry_);
}

}

