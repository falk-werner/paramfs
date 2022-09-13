#include <paramfs/paramfs.hpp>
#include "sample_provider.hpp"

int main(int argc, char* argv[])
{
    paramfs::paramfs filesystem;
    filesystem.add(std::make_shared<paramfs_app::sample_provider>());
    return filesystem.run(argc, argv);
}
