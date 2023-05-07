#ifndef TOKEN_H
#define TOKEN_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*define all the token type the lexer can encounter*/
enum token_type
{
    command,argument,piped,background
};


typedef struct token
{
    char* name;
    enum token_type type;

} token_t;

token_t* create_token(char* name,enum token_type type);
void free_token(token_t* token);
char* token_type(int type);

#endif