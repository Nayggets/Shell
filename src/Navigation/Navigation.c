#include "Navigation.h"

void navigate_to(char* path)
{
    char currentDirectory[1024];

    getcwd(currentDirectory,1024);
    int size = strlen(currentDirectory);
    int pathSize = strlen(path);
    for(int i = 0 ; i < pathSize ; i++){
        currentDirectory[i+size] = path[i];
    }
    int n = chdir(path);
    if(n == -1){
        printf("bash: cd: %s: %s",path,strerror(errno));
    }
}