#include "executor.h"
//Close and dup good entry for process and launch it bg or fg
void launch_process(process_t** process,int nb)
{

    int pid[nb];
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


