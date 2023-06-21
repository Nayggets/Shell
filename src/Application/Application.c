#include "Application.h"

void display_user_credentials();
void free_all(token_t** tokens, command_t** commands, process_t** processes);


int isRunning = 1;
/*
 * use to run args command
 */

void run_inline(char* command)
{
    token_t** tokens = decomposed_command(command);
    if(tokens != NULL){
        int j = 0;
        while(tokens[j] != NULL){
            j++;
        }
        fflush(stdout);
        Init_command_parser(tokens,j);
        if(strcmp(tokens[0]->name,"exit") == 0){
            return;
        }   
        command_t** commands = parse_command();
        int i = 0;
        while(commands[i] != NULL){
            i++;
        }

        process_t** processes = parse_process(commands,i);
        launch_process(processes,i);
        fflush(stdout);
        fflush(stdin);
        free_all(tokens,commands,processes);
    }


}


/*
 * Simply run the terminal using all the component of the system 
 */
void run() 
{
    char buffer[4096];
    while((isRunning) == 1)
    {
        display_user_credentials();
        while(read_line(buffer)){
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
            if(strcmp(tokens[0]->name,"exit") == 0){
                isRunning = 0;
                for(int i = 0 ; tokens[i] != NULL; i++){
                    free_token(tokens[i]);
                }
                free(tokens);
                break;
            }   
            command_t** commands = parse_command();
            int i = 0;
            while(commands[i] != NULL){
                i++;
            }
            
            process_t** processes = parse_process(commands,i);
            launch_process(processes,i);
            fflush(stdout);
            fflush(stdin);
            free_all(tokens,commands,processes);
        }


        
    }


}

/*Free all the memory allocated for the execution of the command line */
void free_all(token_t** tokens, command_t** commands, process_t** processes)
{
    /*----------Token--------------*/
    for(int i = 0 ; tokens[i] != NULL; i++){
        free_token(tokens[i]);
    }
    free(tokens);

    /*---------------Command-------------*/
    for(int i = 0 ; commands[i] != NULL; i++){
        free_command(commands[i]);
    }
    free(commands);
    /*-------------Process-----------*/
    for(int i = 0 ; processes[i] != NULL; i++){
        free_process(processes[i]);
    }
    free(processes);
}

/*display all user information Machine, Username, PWD*/
void display_user_credentials()
{
    char currentDirectory[1024];
    char machineName[128];
    char* userName;

    printf("\n");
    userName = getlogin();
    gethostname(machineName,128);
    getcwd(currentDirectory,1024);
    
    printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[1;36m$ ",userName,machineName,currentDirectory);
    printf("\033[0m"); 
    fflush(stdout);//flush of stdout for better display display
}