# Shell

Simple Shell that manage execution, pipe ,background execution


### Here's a diagram depicting the steps from command line to process execution:

![DIAGRAMME](/ressources/ParsingCommandStep.png "ParsingCommandStep")

First, the user inputs a command line. Next, the lexer tokenizes the raw command. After that, the command parser transforms all the tokens into different commands. The process parser then transforms the commands into processes that are ready to be executed with or without pipes. Finally, the executor launches all the processes.

## Main TODO:
* [x] reader
* [x] lexer
* [x] command_parser
* [x] process_parser 
* [x] executor
* []  Application
* [x] Manage pipe left pipe right and double pipe
* [x] Manage background execution
* [ ] Navigate with cd 
* [ ] Coloration Data
* [ ] Add a module to open a new windows like gnome-terminal
* [ ] Display all information for the user (current directory , User name, Machine name)