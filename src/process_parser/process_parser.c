#include "process_parser.h"
/*Take commands from the command_parser and convert it into process that are ready to be pipe or not and launch in bg or fg*/
process_t** parse_process(command_t** commands,int size)
{
    process_t** processes = malloc(sizeof(process_t*) * size  + 1);
    int i = 0;

    int check = 0;
    int pipefd[2];

    while(i < size){

        processes[i] = create_process(commands[i]);



        if(commands[i]->piped & PIPED_LEFT){
            processes[i]->pipefdInput = pipefd[0];
            
        }


        if(commands[i]->piped & PIPED_RIGHT){

            fflush(stdout);
            check = pipe(pipefd);

            processes[i]->pipefdOutput = pipefd[1];
            if(check == 1){
                exit(-1);
            }
        }

        i++;
    }
    processes[size] = NULL;
    return processes;
}
