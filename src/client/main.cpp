#include "logger.h"

#include "sample.h"

int main(int argc, char* argv[])
{
    init_log(argc, argv);
    LOG(INFO) << hello();
    return 0;
}
