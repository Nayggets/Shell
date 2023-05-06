#include "../../command_parser/command/command.h"
#ifndef PROCESS_H
#define PROCESS_H
typedef struct process{
    command_t* command;
    int pipefdOutput;
    int pipefdInput;

}process_t;
#endif