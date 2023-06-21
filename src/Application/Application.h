#ifndef APPLICATION_H
#define APPLICATION _H
#include "../command_parser/command_parser.h"
#include "../process_parser/process_parser.h"
#include "../reader/reader.h"
#include "../lexer/lexer.h"
#include "../executor/executor.h"
#include "../lexer/token/token.h"
#include <unistd.h>
void run();
void run_inline(char* command);

#endif