#include "sample_provider.hpp"
#include <paramfs/param_error.hpp>

using paramfs::param_error;
using paramfs::status;

namespace paramfs_app
{

sample_provider::sample_provider()
: value_("42")
{

}

std::string const & sample_provider::name() const
{
    return sample_provider::name_;
}

void sample_provider::describe(paramfs::registry_i & registry)
{
    registry.add_param("sample");
}

std::string sample_provider::read(std::string const & path)
{
    if (path == "sample")
    {
        return value_;
    }
    else
    {
        throw param_error(status::bad_unknown_path);
    }
}

void sample_provider::write(std::string const & path, std::string const & value)
{
    if (path == "sample")
    {
        value_ = value;
    }
    else
    {
        throw param_error(status::bad_unknown_path);
    }
}

std::string sample_provider::execute(std::string const & path, std::string const & args)
{
    throw param_error(status::bad_not_implemented, "maybe later ;-)");
}

std::string const sample_provider::name_ = "SampleProvider";

}