#ifndef PARAMFS_REGISTRY_HPP
#define PARAMFS_REGISTRY_HPP

#include "paramfs/registry_i.hpp"
#include "paramfs/provider_i.hpp"

#include <unordered_map>
#include <memory>

namespace paramfs
{

class filesystem;

class registry: public registry_i
{
public:
    explicit registry(filesystem &filesytem);
    ~registry() override = default;
    void add_param(std::string const & path);
    void set_active_provider(std::shared_ptr<provider_i> provider);

private:
    filesystem &filesystem_;
    std::shared_ptr<provider_i> active_provider;
    std::unordered_map<std::string, std::shared_ptr<provider_i>> params;
};

}

#endif
