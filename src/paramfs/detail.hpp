#ifndef PARAMFS_DETAIL_HPP
#define PARAMFS_DETAIL_HPP

#include "paramfs/registry.hpp"
#include "paramfs/filesystem/filesystem.hpp"

namespace paramfs
{

class paramfs::detail
{
public:
    detail(): registry_(filesystem_) { }
    filesystem filesystem_;
    registry registry_;
};

}

#endif
