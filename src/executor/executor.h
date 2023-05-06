#ifndef EXECUTOR_C
#define EXECUTOR_C

#include "../process_parser/process/process.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
void launch_process(process_t** command,int nb);


#endif