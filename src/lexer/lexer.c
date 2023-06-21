#include "lexer.h"
#include <stdarg.h>

char** split_command_args(char* command,int commandSize);
int numberArgs = 0;

/*
 * For error that can occur with background and pipe
 */ 
void lexer_error(token_t* token,int index, const char* msg, ...){
    va_list args;
    va_start(args,msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    exit(-1);
}

/*
 * Take a command from the reader and Decompose it in multiple token with a type
 */
token_t** decomposed_command(char* com)
{
    char** decomposed_arg = split_command_args(com,strlen(com)-1);
    if(decomposed_arg == NULL){
        return NULL;
    }
    token_t** all_token = malloc(sizeof(token_t*) * numberArgs +1);
    int is_argument = 0;
    int already_a_symbol = 0;
    for(int i = 0 ; i < numberArgs ; i++){
        if(decomposed_arg[i][0] == '&'){
            all_token[i] = create_token(decomposed_arg[i],background);
            if(is_argument == 0){
                lexer_error(all_token[i],i,"Background in a wrong place");
            }
            if(already_a_symbol == 1){
                lexer_error(all_token[i],i,"Background next to symbol incorrect");
            }
            already_a_symbol = 1;

            is_argument = 0;
        }
        else if(decomposed_arg[i][0] == '|'){
            all_token[i] = create_token(decomposed_arg[i],piped);
            if(is_argument == 0){
                lexer_error(all_token[i],i,"Piped in a wrong place");
            }
            if(already_a_symbol == 1){
                lexer_error(all_token[i],i,"piped next to symbol incorrect");
            }
            already_a_symbol = 1;
            is_argument = 0;
        }
        else if(is_argument){
            already_a_symbol = 0;

            all_token[i] = create_token(decomposed_arg[i],argument);
        }
        else{
            already_a_symbol = 0;

            all_token[i] = create_token(decomposed_arg[i],command);
            is_argument = 1;
        }
    }
    all_token[numberArgs] = NULL;
    if(strcmp(all_token[0]->name,"exit") == 0){
        for(int i = 0 ; i < numberArgs ; i++){
            free(all_token[i]->name);
            free(all_token[i]);
            free(decomposed_arg[i]);
        }
        free(all_token);
        free(decomposed_arg);
        exit(-1);
    }
    for(int i = 0 ; i < numberArgs ; i++){
        free(decomposed_arg[i]);
    }
    free(decomposed_arg);
    return all_token;
}

/*
 * Update the number of word in the command 
 * also manage chain
 */ 
void update_number_word(char* command,int commandSize)
{
    numberArgs = 0;
    int i = 0;
    while(i < commandSize){//We move from argument to argument by adding 1 to nbWord for each new argument, considering that a string with quotation marks("",'') is counted as a single argument.
        while(i < commandSize && command[i] == ' ' ){
            i++;
        }
        if(i <= commandSize){
            numberArgs++;
        }

        if(command[i] == '\"' || command[i] == '\''){
            i++;
            while(command[i] != '\"' && command[i] != '\''){
                i++;
            }
            i++;
        }
        else{
            while(command[i] != ' ' && i < commandSize){
                i++;
            }
        }
    }
    fflush(stdout);
}


/*
 * Split the command line into multiple arg(char*)
 * also manage "" and ''
 * Exemple if i have in command : cat Makefile | grep 'e' | grep "rm"
 * we obtain char* 1 = cat, char* 2 = Makefile, char* 3 = |, char* 4 = grep, char* 5 = e, char* 6 = |, char* 7 = grep and char* 8 = rm
 */
char** split_command_args(char* command,int commandSize)
{
    update_number_word(command,commandSize);
    if(numberArgs == 0){
        return NULL;
    }
    fflush(stdout);
    /* Updating number of word and allocate memory to store size of all arg and all arg*/
    int* sizePerArg = malloc(sizeof(int) *  numberArgs + 1);
    char** commandArgs = malloc(sizeof(char*) * numberArgs + 1);

    int i = 0;
    int currentArg = 0;
    int sizeCommand = 0;
    while(i-1 < commandSize){ // We will retrieve and store the necessary size for each char*.
        while(command[i] == ' ' && i-1 < commandSize){
            i++;
        }
        if(command[i] == '\"' || command[i] == '\''){
            i++;
            while(command[i] != '\"' && command[i] !=  '\''){
                sizeCommand++;
                i++;
            }
            sizePerArg[currentArg] = sizeCommand;
            i++;
        }
        else{
            while(command[i] != ' ' && i-1 < commandSize){
                sizeCommand++;
                i++;
            }
            sizePerArg[currentArg] = sizeCommand;
        }
        currentArg++;
        sizeCommand = 0;
    }
    for(int i = 0 ; i < numberArgs ; i++){ //allocation of all char* with the size retrieve 
        commandArgs[i] = malloc(sizeof(char) * sizePerArg[i] + 1);
    }

    i = 0;
    sizeCommand = 0;
    currentArg = 0;
    while(i-1 < commandSize){//We will retrieve each argument character by character to store them in their previously allocated char*.
        while(command[i] == ' ' && i-1 < commandSize){
            i++;
        }
        if(command[i] == '\"' || command[i] == '\''){
            i++;
            while(command[i] != '\"' && command[i] != '\''){
                commandArgs[currentArg][sizeCommand] = command[i];
                sizeCommand++;
                i++;
            }
            commandArgs[currentArg][sizeCommand] = '\0';
            i++;
        }
        else{
            while(command[i] != ' ' && i-1 < commandSize){
                commandArgs[currentArg][sizeCommand] = command[i];
                sizeCommand++;
                i++;
            }
            commandArgs[currentArg][sizeCommand] = '\0';
        }
        sizeCommand = 0;
        currentArg++;
    }

    free(sizePerArg);
    commandArgs[currentArg] = NULL;//we fix the end with NULL
    return commandArgs; 
}