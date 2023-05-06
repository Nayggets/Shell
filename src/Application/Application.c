#include "Application.h"

void run()
{
    while(1)
    {
        char* buffer = read_command();
        token_t** Tat = decomposed_command(buffer);
        int j = 0;
        printf("Tokenising : \n\n");
        while(Tat[j] != NULL){
            printf("name : %s \ntoken_type : %s\n\n",Tat[j]->name,token_type(Tat[j]->type));
            j++;
        }
        fflush(stdout);
        Init_command_parser(Tat,j);
        command_t** commands = parse_command();
        int i = 0;
        printf("Parsing of Process :\n\n");
        while(commands[i] != NULL){
            print_command(commands[i]);
            i++;
        }
        fflush(stdout);
        
        process_t** processes = setup_process(commands,i);
        launch_process(processes,i);
        for(int i = 0 ; Tat[i] != NULL; i++){
            free(Tat[i]);
        }

        free(Tat);
        for(int i = 0 ; commands[i] != NULL; i++){
            free(commands[i]);
        }
        free(commands);
        for(int i = 0 ; processes[i] != NULL; i++){
            free(processes[i]);
        }
        free(processes);
    }


}