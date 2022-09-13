#include "paramfs/registry.hpp"
#include "paramfs/param_error.hpp"

namespace paramfs
{

registry::registry()
{

}

void registry::add_param(std::string const & path)
{
    if (!active_provider)
    {
        throw param_error(status::bad_internal_error, "registry has no active provider");
    }

    auto it = params.find(path);
    if (it != params.end())
    {
        throw param_error(status::bad_parameter_already_provided);
    }
}

void registry::set_active_provider(std::shared_ptr<provider_i> provider)
{
    active_provider = provider;
}


}