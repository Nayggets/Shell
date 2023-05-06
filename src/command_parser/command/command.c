#include "command.h"

command_t* create_command()
{
    command_t* command = malloc(sizeof(command_t));
    command->name = NULL;
    command->argument = NULL;
    command->piped = 0;
    command->isBackground = 0;
    return command;
}


command_t* create_command_full(char* _name,char** _argument,char _piped , int _backgrounded)
{
    command_t* command = malloc(sizeof(command_t));
    command->name = _name;
    command->argument = _argument;
    command->piped = _piped;
    command->isBackground = _backgrounded;
    return command;
}



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