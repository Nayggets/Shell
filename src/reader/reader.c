#include "reader.h"
char* read_command()
{
    char* command = malloc(sizeof(char) * 4096);
    int nb_bytes = read(0,command,4096);
    command[nb_bytes-1] = '\0';
    nb_bytes = nb_bytes -2;
    while(nb_bytes > 0 && command[nb_bytes] == ' '){
        command[nb_bytes] = '\0';
        nb_bytes--;
    }

    return command;
}


