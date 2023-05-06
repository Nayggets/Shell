#include "Application.h"

void display_user_credentials();
void free_all(token_t** tokens, command_t** commands, process_t** processes);


void run()
{
    int check;
    char buffer[4096];
    while(1)
    {
        display_user_credentials();
        while(read_command(buffer)){
            display_user_credentials();
        }
        token_t** tokens = decomposed_command(buffer);
        if(tokens != NULL){
            int j = 0;
            while(tokens[j] != NULL){
                j++;
            }
            fflush(stdout);
            Init_command_parser(tokens,j);
            command_t** commands = parse_command();
            int i = 0;
            printf("Parsing of Process :\n\n");
            while(commands[i] != NULL){
                print_command(commands[i]);
                i++;
            }
            
            process_t** processes = setup_process(commands,i);
            launch_process(processes,i);
            fflush(stdout);
            free_all(tokens,commands,processes);
        }


        
    }


}

void free_all(token_t** tokens, command_t** commands, process_t** processes)
{
    for(int i = 0 ; tokens[i] != NULL; i++){
        free(tokens[i]->name);
        free(tokens[i]);
    }

    free(tokens);
    printf("COUCOU");
    fflush(stdout);
    for(int i = 0 ; commands[i] != NULL; i++){
        for(int j = 0 ; commands[i]->argument[j] != NULL ; j++){
            free(commands[i]->argument[j]);
        }
        free(commands[i]->argument);
        free(commands[i]->name);
        free(commands[i]);
    }


        free(commands);
    for(int i = 0 ; processes[i] != NULL; i++){
        free(processes[i]);
    }

        free(processes);
}

void display_user_credentials()
{
    char currentDirectory[1024];
    char machineName[128];
    char* userName;

    printf("\n");
    userName = getlogin();
    gethostname(machineName,128);
    getcwd(currentDirectory,1024);
    
    printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[1;36m$",userName,machineName,currentDirectory);
    printf("\033[0m"); 
    fflush(stdout);//flush de l'entrée standars pour affichage correcte
}