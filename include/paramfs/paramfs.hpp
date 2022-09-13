#ifndef PARAMFS_HPP
#define PARAMFS_HPP

namespace paramfs
{

class paramfs
{
public:
    paramfs();
    ~paramfs();
    int run(int argc, char* argv[]);
private:
    class detail;
    detail * d;
};

};

#endif
