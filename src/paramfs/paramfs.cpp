#include "paramfs/paramfs.hpp"
#include "paramfs/detail.hpp"

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
    return -1;
}

}
