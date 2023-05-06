#include "process_parser.h"
process_t** setup_process(command_t** commands,int size)
{
    process_t** processes = malloc(sizeof(process_t*) * size  + 1);
    int i = 0;

    int check = 0;
    int pipefd[2];

    process_t* process;
    while(i < size){


        process = malloc(sizeof(process_t));
        process->command = commands[i];
        process->pipefdInput = -1;
        process-> pipefdOutput = -1;


        if(commands[i]->piped & PIPED_LEFT){
            printf("%i Hello 2 \n",i);
            process->pipefdInput = pipefd[0];
            
        }


        if(commands[i]->piped & PIPED_RIGHT){

            printf("%i Hello \n",i);
            fflush(stdout);
            check = pipe(pipefd);
            printf("%i pipe 0 \n", pipefd[0]);
            printf("%i pipe 1 \n", pipefd[1]);

            process->pipefdOutput = pipefd[1];
            if(check == 1){
                exit(-1);
            }
        }
        processes[i] = process;
        i++;
        process = NULL;
    }
    processes[size] = NULL;
    return processes;
}
