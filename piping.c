#include "piping.h"
void piping_process(char* process, char* process2)
{
    int fd[2];
    pipe(fd);
    if(fork() != 0){
        close(fd[0]);
        close(STD_OUTPUT);
        dup(fd[1]);
        close(fd[1]);
        execl(process,process,0);
    }
    else{
        close(fd[1]);
        close(STD_INPUT);
        dup(fd[0]);
        close(fd[0]);
        execl(process2,process2,0);
    }
}