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

void paramfs::add(std::shared_ptr<provider_i> provider)
{
    d->registry_.set_active_provider(provider);
    provider->describe(d->registry_);
}

}

