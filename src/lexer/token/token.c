#include "token.h"

/*
 * Allocated memory for token and filled the structure
 */
token_t* create_token(char* name,enum token_type type)
{
    token_t* create = malloc(sizeof(token_t));
    create->name = strdup(name);
    create->type = type;
    return create;
}

/*
 * Free the allocated Memory for the structure token_t
 */
void free_token(token_t* toFree)
{
    free(toFree->name);
    free(toFree);
}

/*
 * Return the token type in char* for debuging or/and print
 */ 
char* token_type(int type)
{
    switch (type)
    {
    case 0:
        /* code */
        return "TokenName";
    break;
    case 1:
        /* code */
        return "TokenArgument";
    break;    
    case 2:
        /* code */
        return "TokenPipe";
    break;    
    case 3:
        /* code */
        return "TokenBackground";
    break;    
    default:
        break;
    }
    return NULL;
}