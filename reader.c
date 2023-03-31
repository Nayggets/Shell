

char* read_command()
{
    char command[4096];
    int nb_bytes = read(0,command,4096);
    command[nb_bytes] = '\0';

    return command;
}


