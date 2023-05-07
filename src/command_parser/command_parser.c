#include "command_parser.h"




/*init the parser*/
void Init_command_parser(token_t** tokens, int size)
{
    token_of_command = tokens;
    size_of = size;
}


/*Parse all the token in command*/
command_t** parse_command()
{
    int index = 0;
    int j = 0;
    int numbercommand = 1;
    while(j != size_of){
        if(token_of_command[j]->type == 2 || token_of_command[j]->type == 3){
            numbercommand++;
        }
        j++;

    }

    command_t** commands = malloc(sizeof(command_t*) * numbercommand + 1);


    for(int i = 0 ; i < numbercommand ; i++){
        commands[i] = parse_simple_command(&index);


    }
    commands[numbercommand] = NULL;
    return commands;
}



/*Parse a certain number of token into a command 
 *exemple if all token is like that 0.cat 1.Makefile 2.| 3.grep 4.e
 *the return command will be cat Makefile with the mask pipe_right and no background
 */
command_t* parse_simple_command(int* index)
{

    int piped = 0;
    if(token_of_command[*index]->type == 2){
        piped |= PIPED_LEFT;
        (*index)++;
    }
    else if(token_of_command[*index]->type == 3){
        (*index)++;
    }
    if(*index == size_of){
        return NULL;
    }
    int j = *index;
    while(j != size_of && token_of_command[j]->type != 2 && token_of_command[j]->type != 3){
        j++;
    }
    int limit = j;

    j = j - (*index);

    char** parameter = malloc(sizeof(char*) * j+1);

    char* name ;

    int first = 1;
    int i = 0;
    j = 0;
    while(*index != limit && token_of_command[*index]->type != 2 && token_of_command[*index]->type != 3){
        if(first == 1){
            name = malloc(sizeof(char) * strlen(token_of_command[*index]->name));
            name = strcpy(name,token_of_command[*index]->name);
            parameter[j] = malloc(sizeof(char) * strlen(token_of_command[*index]->name));
            parameter[j] = strcpy(parameter[j],token_of_command[*index]->name);
            j++;
            first = 0;
        }
        else{
            parameter[j] = malloc(sizeof(char) * strlen(token_of_command[*index]->name));
            parameter[j] = strcpy(parameter[j],token_of_command[*index]->name);
            j++;
        }

        (*index)++;
    }
    fflush(stdout);
    parameter[j] = NULL;
    int backgrounded = 0;
    if(*index < size_of && token_of_command[*index]->type == 2){
        piped |= PIPED_RIGHT;

    }
    else if(*index < size_of && token_of_command[*index]->type == 3){
        backgrounded = 1;
    }

    command_t* command = create_command(name,parameter,piped,backgrounded);

    return command;
}


