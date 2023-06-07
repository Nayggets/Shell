#include "../../command_parser/command/command.h"
#ifndef PROCESS_H
#define PROCESS_H
typedef struct process{
    command_t* command;
    int pipefdOutput;
    int pipefdInput;

}process_t;

process_t* create_process(command_t* _command);
void free_process(process_t* process);
void print_process(const process_t* process);
#endif