#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H
#include "./command/command.h"
#include "../lexer/token/token.h"


static token_t** token_of_command;

static int size_of = 0;


void Init_command_parser(token_t** tokens,int size);

command_t* parse_simple_command(int* index);

command_t** parse_command();

#endif