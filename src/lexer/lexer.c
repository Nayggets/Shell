#include "lexer.h"
#include <stdarg.h>

char** split_command_args(char* command,int commandSize);
int numberArgs = 0;

void lexer_error(token_t* token,int index, const char* msg, ...){
    va_list args;
    va_start(args,msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    exit(-1);
}

/*Take a command from the reader and Decompose it in multiple token with a type*/
token_t** decomposed_command(char* com)
{
    char** decomposed_arg = split_command_args(com,strlen(com)-1);
    token_t** all_token = malloc(sizeof(token_t*) * numberArgs );
    printf("%i", numberArgs);
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
        exit(-1);
    }
    return all_token;
}

void update_number_word(char* command,int commandSize)
{
    numberArgs = 0;
    int i = 0;
    while(i < commandSize){//on ce deplace d'argument en argument en ajoutant ++ a nbWord a chaque nouvelle argument en comptant que une chaine de caractères avec des "" est un seul argument.
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
}


char** split_command_args(char* command,int commandSize)
{
    update_number_word(command,commandSize);
    /* recuperation du nombre d'argument et allocation des tableau*/
    int* sizePerArg = malloc(sizeof(int) * numberArgs + 1);
    char** commandArgs = malloc(sizeof(char*) * numberArgs + 1);

    int i = 0;
    int currentArg = 0;
    int sizeCommand = 0;
    while(i-1 < commandSize){ // on va recuperer et stocker la taille nescessaire pour chaque chaine de caracteres de chaque argument
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
    for(int i = 0 ; i < numberArgs ; i++){ //allocation des chaines par taille recuperer 
        commandArgs[i] = malloc(sizeof(char) * sizePerArg[i] + 1);
    }

    i = 0;
    sizeCommand = 0;
    currentArg = 0;
    while(i-1 < commandSize){// on va recuperer chaque arguments caracteres par caracteres pour les stockers dans leur chaine allouer precedemment
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
    commandArgs[currentArg] = NULL;//on fixe la fin du tableau de chaine
    return commandArgs; 
}