#ifndef PARAMFS_PARAMVALUE_NODE_HPP
#define PARAMFS_PARAMVALUE_NODE_HPP

#include "paramfs/filesystem/node_i.hpp"
#include "paramfs/provider_i.hpp"

namespace paramfs
{

class paramvalue_node: public node_i
{
public:
    paramvalue_node(std::string const & path, std::shared_ptr<provider_i> provider);
    ~paramvalue_node() override = default;
    std::string const & name() const override;
    int mode() const override;
    bool is_dir() const override;
    node_i * get_child(std::string const & name) override;
    void iterate_child_nodes(std::function<void(node_i &)> visit) override;
    void add_child(std::unique_ptr<node_i> node) override;
    std::unique_ptr<pseudofile_i> open_for_read() override;
    std::unique_ptr<pseudofile_i> open_for_write() override;
private:
    std::string const path_;
    std::shared_ptr<provider_i> provider_;
};

}

#endif
