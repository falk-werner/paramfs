#ifndef PARAMFS_STATIC_FILE_HPP
#define PARAMFS_STATIC_FILE_HPP

#include "paramfs/filesystem/node_i.hpp"

namespace paramfs
{

class static_file: public node_i
{
public:
    static_file(std::string const & name, std::string const & contents);
    std::string const & name() const override;
    int mode() const override;
    bool is_dir() const override;
    node_i * get_child(std::string const & name) override;
    void iterate_child_nodes(std::function<void(node_i &)> visit) override;
    void add_child(std::unique_ptr<node_i> node) override;
    std::string get_contents() override;
private:
    std::string name_;
    std::string contents_;
};

}

#endif
