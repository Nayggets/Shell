#include "../Application/Application.h"
int main(int argc, char* argv[])
{
    initReader();
    run();
    freeReader();
}