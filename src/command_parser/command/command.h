#ifndef COMMAND_H
#define COMMAND_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct command
{
    char* name;
    char** argument;
    char piped;
    int isBackground;

} command_t;

enum pipe
{
    PIPED_LEFT = 0b00000001,
    PIPED_RIGHT = 0b00000010
};


command_t* create_command();
command_t* create_command_full(char* _name,char** _argument,char _piped , int _backgrounded);
void print_command(command_t* command);

#endif