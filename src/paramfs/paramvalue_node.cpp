#include "paramfs/paramvalue_node.hpp"
#include "paramfs/param_error.hpp"
#include "paramfs/filesystem/infile.hpp"
#include "paramfs/filesystem/outfile.hpp"

namespace
{

std::string const paramvalue_node_name = "value";

}

namespace paramfs
{

paramvalue_node::paramvalue_node(std::string const & path, std::shared_ptr<provider_i> provider)
: path_(path)
, provider_(provider)
{

}

std::string const & paramvalue_node::name() const 
{
    return paramvalue_node_name;
}

int paramvalue_node::mode() const
{
    return 0666;
}

bool paramvalue_node::is_dir() const
{
    return false;
}

node_i * paramvalue_node::get_child(std::string const & name)
{
    (void) name;
    return nullptr;
}

void paramvalue_node::iterate_child_nodes(std::function<void(node_i &)> visit)
{
    (void) visit;
}

void paramvalue_node::add_child(std::unique_ptr<node_i> node)
{
    throw param_error(status::bad_internal_error, "no dir");
}

std::unique_ptr<pseudofile_i> paramvalue_node::open_for_read()
{
    return std::make_unique<infile>(provider_->read(path_));
}

std::unique_ptr<pseudofile_i> paramvalue_node::open_for_write()
{
    std::string path = path_;
    std::shared_ptr<provider_i> provider = provider_;
    return std::make_unique<outfile>([path, provider](char const * data, size_t length) {
        provider->write(path, std::string(data, length));
    });
}


}