# Shell

## Description
Simple shell that can manage command execution, piping of commands, and background execution.


### Diagram depicting the steps from command line to process execution:

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
### process_section
+ launch_process --> 2 * O(n)
+ setup_process --> O(n)
### reader_section
+ read_command  --> O(n)
### free_section
+ free_all      --> O(n²)
+ free_token    --> 1 
+ free_process  --> O(n)
+ free_command  --> O(n)

## About memory

When running and executing a simple command, such as "cat Makefile", the program employs approximately 20,034 bytes of memory through 40 allocations.

When running and executing a more complex command, such as "cat Makefile | grep e | grep rm", the program employs approximately 20,243 bytes of memory through 70 allocations.

### Valgrind check : 

According to Valgrind memory check, the program does not have any memory leaks. All memory allocated in the heap is properly freed.

## About Tools use in this project

+ IDE : Visual studio code 
+ Debugger : gdb and Visual studio code Debugger (70/30)
+ Memory check : Valgrind 
+ Compiler : mingw 
+ Operating System : Ubuntu(64bit)
+ Tools of Updating and Versionning : Git
+ Diagram : Excalidraw


