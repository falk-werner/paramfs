#include "paramfs/registry.hpp"
#include "paramfs/param_error.hpp"
#include "paramfs/filesystem/filesystem.hpp"
#include "paramfs/paramvalue_node.hpp"

namespace paramfs
{

registry::registry(filesystem & filesystem)
: filesystem_(filesystem)
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

    params[path] = active_provider;
    filesystem_.add(path, std::make_unique<paramvalue_node>(path, active_provider));
}

void registry::set_active_provider(std::shared_ptr<provider_i> provider)
{
    active_provider = provider;
}


}