#include "hsa.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: hsa [savefile] [output]\n");
        return 1;
    }

    hsaWriteXml(hsaLoadFile(argv[1]), argv[2]);

    return 0;
}
