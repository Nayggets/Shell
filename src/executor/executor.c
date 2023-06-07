#include "executor.h"
/*
 * Close and dup good entry for process and launch it bg or fg
 */
void launch_process(process_t** process,int nb)
{
    int pid[nb];
    int uniquePid = 0;
    int check = 0;
    for(int i = 0 ; i < nb ; i++){
        if(strcmp(process[i]->command->name,"cd") == 0){ // Change to if execvp fail check all the builtin function. line 33-36
            pid[i] = -1;
            navigate_to(process[i]->command->argument[1]);
        }
        else{

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
                check = execvp(process[i]->command->name,process[i]->command->argument);
                //check builtin or error
                if(check != 0){
                    printf("%s : command not found",process[i]->command->name);
                    exit(-1);
                }
            }
            else{
                close(process[i]->pipefdInput);
                close(process[i]->pipefdOutput);

            }
            pid[i] = uniquePid;
        }
    }
    
    for(int i = 0 ; i < nb ; i++){
        if(process[i]->command->isBackground == 0){
            waitpid(pid[i],NULL,0);
        }
    }
    fflush(stdin);
    fflush(stdout);
    
}


