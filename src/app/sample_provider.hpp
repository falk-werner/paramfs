#ifndef PARAMFS_SAMPLE_PROVIDER_HPP
#define PARAMFS_SAMPLE_PROVIDER_HPP

#include <paramfs/provider_i.hpp>
#include <paramfs/registry_i.hpp>


namespace paramfs_app
{

class sample_provider: public paramfs::provider_i
{
public:
    sample_provider();
    ~sample_provider() = default;

    std::string const & name() const override;
    void describe(paramfs::registry_i & registry) override;
    std::string read(std::string const & path) override;
    void write(std::string const & path, std::string const & value) override;
    std::string execute(std::string const & path, std::string const & args) override;
public:
    static std::string const name_;
    std::string value_;
};

}

#endif
