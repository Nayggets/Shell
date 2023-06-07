#include "command.h"



/*
 * alloc and return the command filled
 */
command_t* create_command(char* _name,char** _argument,char _piped , int _backgrounded)
{
    command_t* command = malloc(sizeof(command_t));
    command->name = _name;
    command->argument = _argument;
    command->piped = _piped;
    command->isBackground = _backgrounded;
    return command;
}

/* 
 * free the memory of the structure
 */
void free_command(command_t* command)
{
    for(int j = 0 ; command->argument[j] != NULL ; j++){
        free(command->argument[j]);
    }
    free(command->argument);
    free(command->name);
    free(command);
}

/*
 * print name arguments pipe state and background state 
 */
void print_command(command_t* command)
{
    printf("commandname --> %s \n",command->name);
    int i = 0;
    while(command->argument[i] != NULL){
        printf("argument %i ----> %s\n",i,command->argument[i]);
        i++;
    }
    printf("piped state --->  %i\n",command->piped);
    printf("background state ---> %i\n\n",command->isBackground);
}