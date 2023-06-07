#ifndef READER_H
#define READER_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
enum key 
{
    ENTER = 10,
    ARROW = 27,
    BACKWARD = 127

};

enum dir_arrow
{
    RIGHT_ARROW = 67,
    LEFT_ARROW = 68,
    UP_ARROW = 65, 
    DOWN_ARROW = 66
};


int read_line(char* command);
void freeReader();
void initReader();
int read_command(char* command);

#endif