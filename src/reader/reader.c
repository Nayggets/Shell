#include "reader.h"


static struct termios old;

static struct termios current;



char* history[1024];
static int nbHistory;
static int cursorHistory;
/*
 * Initialise IO settings 
 */
void init_term_io_settings()
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    current = old; /* copy to modify attribute */
    current.c_lflag &= ~ICANON; /* disable the enter to get value */
    current.c_lflag &= ~ECHO; /* set no echo mode */
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/*
 * Move the cursorHistory UP
 */
int cursorUp()
{
    if(cursorHistory > 0){
        cursorHistory--;
        return 0;
    }
    printf("\a");
    return 1;
}

/*
 * Move the cursorHistory Down
 */
int cursorDown()
{
    if(cursorHistory < nbHistory){
        cursorHistory++;
        return 0;
    }
    
    printf("\a");
    return 1;
}


/*
 * Reset to the original settings of the terminal I/O
 */
void reset_term_io_settings(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/*
 * Init The history and load the old line using the history.txt file
 */
void initReader()
{
    nbHistory = 0;
    
    int fd = open("history.txt", O_RDONLY | O_CREAT ,0600);
    if(fd == -1){
        perror("open");
    }
    char buffer[128];
    char command[4096];
    int index = 0;
    int nb = 0;
    while((nb = read(fd,buffer,128)) != 0){
        buffer[nb] = '\0';
        for(int i = 0 ; i < nb ; i++){
            if(buffer[i] == '\n'){
                command[index] = '\0';
                history[nbHistory] = malloc(index + 1);
                memcpy(history[nbHistory],command,index+1);
                nbHistory++;
                index = 0;
            }
            else{
                command[index] =  buffer[i];
                index++;
            }
        }
    }
    cursorHistory = nbHistory;
}

/*
 * Free the alocated memory for the history
 */
void freeReader()
{
    for(int i = nbHistory-1 ; i >= 0 ; i--){ 
        free(history[i]);
    }
}

/*
 * Load into the line a command of the history using the number for the position 
 */
int load_history(int number,char* command)
{
    fflush(stdout);
    strcpy(command,history[number]);
    int size = strlen(history[number]);
    command[size] = '\0';
    return size;
    
}

/*
 * Read a Line
 * allow the user to move into it command to modify using the cursor controlled by the arrow 
 * the user can charge old command from the history 
 * every command the user wrote is stock in a history
 * 
 */
int read_line(char* command)
{
    memset(command,0,4095);
    init_term_io_settings();
    int index = 0;
    int maxSize = 0;
    int endOfLine = 0;
    char c = 0;
    char* toDisplay;
    while(!endOfLine)
    {
        c = getchar();
        switch(c)
        {
            case BACKWARD:
            {

                if(index != 0){
                    index--;
                    for(int i = index ; i <= maxSize ; i++){
                        command[i] = command[i+1];
                    }
                    maxSize--;
                    printf("\033[%dD",1);
                    command[maxSize] = '\0';
                    for(int i = index ; i <= maxSize ; i++){
                        printf("%c",command[i]);
                    }
                    printf(" ");
                    printf("\033[%dD",(maxSize-(index)+1));



                }

                break;
            }
            case ENTER:
            {
                endOfLine = 1;
                command[index] = '\0';
                printf("\n");
                break;
            }
            case ARROW:
            {
                getchar();
                c = getchar();
                switch (c)
                {
                    case RIGHT_ARROW:
                    {
                        if(maxSize != index){ // right deplacement
                            printf("\033[%dC",1);
                            index++;
                        }
                        break;

                    }
                    case LEFT_ARROW:
                    {
                        if(index > 0){ // left deplacement
                            printf("\033[%dD",1);
                            index--;


                        }
                        break;
                    }
                    case UP_ARROW:
                    {
                        if(!cursorUp()){
                            while(index != maxSize){
                                printf("\033[%dC",1);
                                index++;
                            }
                            while(index != 0){
                                printf("\b \b");
                                index--;
                            }
                            //printf("\033[%dD",index);
                            //index = 0;
                            //for(int i = 0 ; i < maxSize ; i++){
                              //  printf(" ");
                               // command[i] = 0;
                            //}
                            
                            //printf("\033[%dD",maxSize);

                            maxSize = load_history(cursorHistory,command);
                            printf("%s",command);
                            index = maxSize;
                        }
                        break;
                    }
                    case DOWN_ARROW:
                    {
                        if(!cursorDown()){
                            if(nbHistory == cursorHistory){
                                /*printf("\033[%dD",index);
                                index = 0;
                                for(int i = 0 ; i <= maxSize ; i++){
                                    printf(" ");
                                    command[i] = 0;
                                }
                                printf("\033[%dD",maxSize);
                                */
                                while(index != maxSize){
                                    printf("\033[%dC",1);
                                    index++;
                                }
                                while(index != 0){
                                    printf("\b \b");
                                    index--;
                                }   
                                maxSize = 0;
                                index = 0;
                            }
                            else{
                                /*printf("\033[%dD",index);
                                index = 0;
                                for(int i = 0 ; i < maxSize ; i++){
                                    printf(" ");
                                    command[i] = 0;
                                }
                                printf("\033[%dD",maxSize);
                                */
                                while(index != maxSize){
                                    printf("\033[%dC",1);
                                    index++;
                                }
                                while(index != 0){
                                    printf("\b \b");
                                    index--;
                                }   
                                maxSize = load_history(cursorHistory,command);
                                printf("%s",command);
                                index = maxSize;
                            }

                            
                        }
                        break;
                    }
                    
                    default:
                        break;

                    }
                break;
            }
            default:
            {
                for(int i = maxSize ; i > index ; i--){
                    command[i] = command[i-1];
                }
                command[index] = c;
                for(int i = index ; i <= maxSize ; i++){
                    printf("%c",command[i]);
                }
                maxSize++;
                command[maxSize] = '\0';
                index++;

                if(index == 1 && maxSize != 1){
                    printf("\033[%dD",(maxSize-(index)));
                }
                else if(index != maxSize && index != 0){
                    printf("\033[%dD",(maxSize-(index)));
                }
                else{
                    printf("\033[%dD",(maxSize-(index+1)));
                }
                break;
            }
            
        }


    }

    reset_term_io_settings();
    int fd = open("history.txt",O_WRONLY);
    lseek(fd,0,SEEK_END);

    command[maxSize] = '\0';
    while(maxSize > 0 && command[maxSize] == ' '){
        command[maxSize] = '\0';
        maxSize--;
    }
    if(maxSize == 0){
        return 1;
    }
    if(nbHistory == 0 || strcmp(command,history[nbHistory-1]) != 0 ){
        command[maxSize] = '\n';
        write(fd,command,strlen(command));
    } 
    
    command[maxSize] = '\0';
    history[nbHistory] = malloc(strlen(command));
    strcpy(history[nbHistory],command);
    nbHistory++;
    cursorHistory = nbHistory;
    return 0;
}

int read_command(char* command)
{
    int nbBytes = 1;
    nbBytes = read(0,command,4096);
    command[nbBytes-1] = '\0';
    if(nbBytes == 1){
        return 1;
    }
    nbBytes = nbBytes -2;
    while(nbBytes > 0 && command[nbBytes] == ' '){
        command[nbBytes] = '\0';
        nbBytes--;
    }
    return 0;
}