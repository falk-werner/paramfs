#include "paramfs/paramfs.hpp"
#include "paramfs/detail.hpp"
#include "paramfs/filesystem/static_file.hpp"

#define FUSE_USE_VERSION 31
#include <fuse.h>

#include <errno.h>

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
    try
    {
        auto * filesystem = get_filesystem();
        return filesystem->access(path, mask);
    }
    catch (...)
    {
        return -ENOENT;
    }
}

int fs_getattr(char const * path, struct stat * buffer, fuse_file_info * fi)
{
    try
    {
        auto * filesystem = get_filesystem();
        uint64_t * handle = (nullptr != fi) ? &fi->fh : nullptr;
        return filesystem->getattr(path, buffer, handle);
    }
    catch (...)
    {
        return -ENOENT;
    }
}

int fs_readdir(char const * path, void * buffer, fuse_fill_dir_t filler, off_t offset, fuse_file_info * fi, fuse_readdir_flags flags)
{
    try
    {
        auto * filesystem = get_filesystem();
        return filesystem->readdir(path, [buffer, &filler](auto const & name) {
            filler(buffer, name.c_str(), nullptr, 0, static_cast<fuse_fill_dir_flags>(0));
        });
    }
    catch (...)
    {
        return -ENOENT;
    }
}

int fs_open(char const * path, fuse_file_info * fi)
{
    try
    {
        auto * filesystem = get_filesystem();
        return filesystem->open(path, fi->flags, fi->fh);
    }
    catch (...)
    {
        return -ENOENT;
    }
}

int fs_release(char const * path, fuse_file_info * fi)
{
    try
    {
        auto * filesystem = get_filesystem();
        filesystem->release(fi->fh);
    }
    catch (...)
    {
        // swallow
    }

    return 0;
}

int fs_read(char const * path, char * buffer, size_t size, off_t offset, fuse_file_info * fi)
{
    (void) path;

    try
    {
        auto * filesystem = get_filesystem();
        return filesystem->read(fi->fh, buffer, size, offset);
    }
    catch (...)
    {
        return -ENOENT;
    }
}

int fs_write(const char * path, const char * buffer, size_t size, off_t offset, struct fuse_file_info * fi)
{
    (void) path;

    try
    {
        auto * filesystem = get_filesystem();
        return filesystem->write(fi->fh, buffer, size, offset);
    }
    catch (...)
    {
        return -ENOENT;
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
    ops.write = fs_write;

    void * filesystem = reinterpret_cast<void*>(&d->filesystem_);
    return fuse_main(argc, argv, &ops, filesystem);
}

void paramfs::add(std::shared_ptr<provider_i> provider)
{
    d->registry_.set_active_provider(provider);
    provider->describe(d->registry_);
}

}

