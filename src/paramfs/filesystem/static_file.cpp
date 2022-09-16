#include "paramfs/filesystem/static_file.hpp"
#include "paramfs/filesystem/infile.hpp"
#include "paramfs/param_error.hpp"

namespace paramfs
{

static_file::static_file(std::string const & name, std::string const & contents)
: name_(name)
, contents_(contents)
{

}

std::string const & static_file::name() const
{
    return name_;
}

int static_file::mode() const
{
    return 0444;
}

bool static_file::is_dir() const
{
    return false;
}

node_i * static_file::get_child(std::string const & name)
{
    return nullptr;
}

void static_file::iterate_child_nodes(std::function<void(node_i &)> visit)
{
    (void) visit;
}

void static_file::add_child(std::unique_ptr<node_i> node)
{
    throw param_error(status::bad_internal_error, "no dir");
}

std::unique_ptr<pseudofile_i> static_file::open_for_read()
{
    return std::make_unique<infile>(contents_);
}

std::unique_ptr<pseudofile_i> static_file::open_for_write()
{
    throw param_error(status::bad_internal_error, "no contents");
}

}