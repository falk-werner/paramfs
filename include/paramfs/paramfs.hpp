#ifndef PARAMFS_HPP
#define PARAMFS_HPP

#include <memory>

namespace paramfs
{

class provider_i;

class paramfs
{
public:
    paramfs();
    ~paramfs();
    int run(int argc, char* argv[]);
    void add(std::shared_ptr<provider_i> provider);
private:
    class detail;
    detail * d;
};

};

#endif
