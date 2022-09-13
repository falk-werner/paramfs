#include <paramfs/paramfs.hpp>

int main(int argc, char* argv[])
{
    paramfs::paramfs filesystem;
    return filesystem.run(argc, argv);
}
