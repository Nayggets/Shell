#include "../Application/Application.h"


char* treat_args_for_inline(int argc,char* argv[])
{
    int argSize = 0;
    if(argc > 1){
        for(int i = 1 ; i < argc ; i++){
            argSize += strlen(argv[i]);
        }
    }
    char* concatArgs = malloc(argSize + (argc-1));
    for(int i = 1 ; i < argc ; i++){
        strcat(concatArgs,argv[i]);
        strcat(concatArgs," ");
    }    
    int i = argSize + argc-2;
    while(concatArgs[i] == ' ' || concatArgs[i] == '\n')
    {
        concatArgs[i] = '\0';
        i--;
    }
    return concatArgs;
}


int main(int argc, char* argv[])
{
    char* concatArgs = treat_args_for_inline(argc,argv);
    run_inline(concatArgs);
    free(concatArgs);
    initReader();
    run();
    freeReader();
}