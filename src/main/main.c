#include "../Application/Application.h"

int main(int argc, char* argv[])
{
    if(argc > 1){
        run_inline(argv[1]);
        return 0;
    }
    initReader();
    run();
    freeReader();
}
