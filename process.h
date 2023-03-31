

struct process
{
    char* process;
    char** argument;
    char piped;
};

enum pipe
{
    left_pipe = 0b00000001,
    right_pipe = 0b00000010
};