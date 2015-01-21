#include "logger.h"

INITIALIZE_EASYLOGGINGPP

// Load configuration from file and configure all loggers
void init_log(int argc, char* argv[])
{
  el::Configurations conf("log/log.conf");
  el::Loggers::reconfigureAllLoggers(conf);
  START_EASYLOGGINGPP(argc, argv);
}
