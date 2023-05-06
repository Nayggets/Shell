#include "executor.h"
void launch_process(process_t** process,int nb)
{
    for(int i = 0 ; i < nb ; i++){
        printf("process %s :  \npipeInput : %i \n pipeOutput : %i\n",process[i]->command->name,process[i]->pipefdInput,process[i]->pipefdOutput);
    }
    fflush(stdout);
    int* pid = malloc(sizeof(int) * nb);
    int uniquePid = 0;
    for(int i = 0 ; i < nb ; i++){
        uniquePid = fork();
        
        if(uniquePid == 0){
            if(process[i]->pipefdOutput != -1){
                close(process[i+1]->pipefdInput);
                dup2(process[i]->pipefdOutput,1);
                close(process[i]->pipefdOutput);
            }
            if(process[i]->pipefdInput != -1){
                close(process[i-1]->pipefdOutput);
                dup2(process[i]->pipefdInput,0);
                close(process[i]->pipefdInput);

            }
            execvp(process[i]->command->name,process[i]->command->argument);
        }
        else{
            close(process[i]->pipefdInput);
            close(process[i]->pipefdOutput);

        }
        pid[i] = uniquePid;
    }
    
    for(int i = 0 ; i < nb ; i++){
        if(process[i]->command->isBackground == 0){
            waitpid(pid[i],NULL,0);
        }
    }
    
    
}


process_t** setup_process(command_t** commands,int size)
{
    process_t** processes = malloc(sizeof(process_t*) * size + 1);
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
    return processes;
}
