#include "reader.h"
int read_command(char* command)
{
    int nb_bytes = 1;
    nb_bytes = read(0,command,4096);
    command[nb_bytes-1] = '\0';
    if(nb_bytes == 1){
        return 1;
    }
    nb_bytes = nb_bytes -2;
    while(nb_bytes > 0 && command[nb_bytes] == ' '){
        command[nb_bytes] = '\0';
        nb_bytes--;
    }
    return 0;
}