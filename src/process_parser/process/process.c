#include "process.h"

/*alloc and return the command filled*/
process_t* create_process(command_t* _command)
{
        process_t* process = malloc(sizeof(process_t));
        process->command = _command;
        process->pipefdInput = -1;
        process-> pipefdOutput = -1;
    return process;
}

/*Free the memory allocated to process structure*/
void free_process(process_t* process)
{
    free(process);
}