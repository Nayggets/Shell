# Shell

## Description
Simple shell that can manage command execution, piping of commands, and background execution.


### Here's a diagram depicting the steps from command line to process execution:

![DIAGRAMME](/ressources/ParsingCommandStep.png "ParsingCommandStep")

First, the user inputs a command line. Next, the lexer tokenizes the raw command. After that, the command parser transforms all the tokens into different commands. The process parser then transforms the commands into processes that are ready to be executed with or without pipes. Finally, the executor launches all the processes.

## Main TODO:
* [x] reader
* [x] lexer
* [x] command_parser
* [x] process_parser 
* [x] executor
* [x] Application
* [x] Manage pipe left pipe right and double pipe
* [x] Manage background execution
* [ ] Navigate with cd 
* [ ] Coloration Data
* [ ] Add a module to open a new windows like gnome-terminal
* [x] Display all information for the user (current directory , User name, Machine name)
* [ ] autoCompletion Command



## About complexity 
launch_process --> 3 * O(n)

## About memory

for a run and exec simple command(like cat Makefile) the program use approximately 20034 bytes for 40 allocs
for a run and exec a more huge command(like cat Makefile | grep e | grep rm) the program use approximately 20243 bytes for 70 alloc

### Valgrind check : 

According to Valgrind, the program does not have any memory leaks. All memory allocated in the heap is properly freed.