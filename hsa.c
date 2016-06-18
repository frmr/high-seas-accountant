#include <stdio.h>

#include "hsa.h"

int main(int argc, char* argv[])
{
    hsaGameData gameData;
    hsaLoadFile(argv[1], &gameData);
    hsaToCsv(&gameData, "test.txt");
    
    return 0;
}
