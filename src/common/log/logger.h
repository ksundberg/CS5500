#ifndef LOGGER_H_
#define LOGGER_H_

#define ELPP_THREAD_SAFE
#define ELPP_NO_DEFAULT_LOG_FILE
#include "easylogging++.h"

void init_log(int argc, char* argv[]);

#endif
