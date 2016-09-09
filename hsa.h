#include <stdio.h>

#define HSA_NUM_OF_COMMODITIES  15
#define HSA_NUM_OF_PORTS        62

typedef enum
{
    HSA_COFFEE = 0,
    HSA_GRAIN = 1,
    HSA_SUGAR = 2,
    HSA_TEA = 3,
    HSA_ARMS = 4,
    HSA_COTTON = 5,
    HSA_WOOL = 6,
    HSA_FURS = 7,
    HSA_IVORY = 8,
    HSA_JEWELRY = 9,
    HSA_SILK = 10,
    HSA_SPICES = 11,
    HSA_LIQUOR = 12,
    HSA_OPIUM = 13,
    HSA_TOBACCO = 14
} hsaCommodityType;

const char* const hsaCommodityNames[HSA_NUM_OF_COMMODITIES] = {"COFFEE", "GRAIN", "SUGAR", "TEA", "ARMS", "COTTON", "WOOL", "FURS", "IVORY", "JEWELRY", "SILK", "SPICES", "LIQUOR", "OPIUM", "TOBACCO"};

typedef struct
{
    int                 quantity;
    int                 buyFor;
    int                 sellFor;
} hsaCommodity;

typedef struct
{
    char            name[20];
    hsaCommodity    commodities[HSA_NUM_OF_COMMODITIES];
} hsaPort;

typedef struct
{
    int         gold;
    char        playerName[20];
    char        shipName[20];
    hsaPort     ports[HSA_NUM_OF_PORTS];
} hsaGameData;

hsaPort hsaLoadPort(FILE* file)
{
    hsaPort port;

    fread(port.name, 1, 20, file);

    fseek(file, 373, SEEK_CUR);
    for (int i = 0; i < HSA_NUM_OF_COMMODITIES; ++i)
    {
        fread(&port.commodities[i].quantity, 4, 1, file);
    }

    for (int i = 0; i < HSA_NUM_OF_COMMODITIES; ++i)
    {
        fread(&port.commodities[i].buyFor, 4, 1, file);
        port.commodities[i].sellFor = port.commodities[i].buyFor * 0.91;
    }

    return port;
}

hsaGameData hsaLoadFile(const char* filename)
{
    hsaGameData gameData;

    FILE* file = fopen(filename, "rb");

    fseek(file, 6264, SEEK_SET);

    for (int i = 0; i < HSA_NUM_OF_PORTS; ++i)
    {
        gameData.ports[i] = hsaLoadPort(file);
        fseek(file, 6, SEEK_CUR);
    }

    fseek(file, 38719, SEEK_SET);
    fread(&gameData.gold, 4, 1, file);
    fread(&gameData.playerName, 1, 20, file);
    fread(&gameData.shipName, 1, 20, file);

    fclose(file);

    return gameData;
}

void hsaWriteXml(const hsaGameData gameData, const char* const filename)
{
    FILE* file = fopen(filename, "w");

    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n");
    fprintf(file, "<gamedata>\n");

    for (unsigned int portIndex = 0; portIndex < HSA_NUM_OF_PORTS; ++portIndex)
    {
        fprintf(file, "\t<port>\n");
        fprintf(file, "\t\t<name>%s</name>\n", gameData.ports[portIndex].name);
        fprintf(file, "\t\t<commodities>\n");

        for (unsigned int commodityIndex = 0; commodityIndex < HSA_NUM_OF_COMMODITIES; ++commodityIndex)
        {
            fprintf(file, "\t\t\t<commodity>\n");
            fprintf(file, "\t\t\t\t<name>%s</name>\n", hsaCommodityNames[commodityIndex]);
            fprintf(file, "\t\t\t\t<quantity>%d</quantity>\n", gameData.ports[portIndex].commodities[commodityIndex].quantity);
            fprintf(file, "\t\t\t\t<buy>%d</buy>\n", gameData.ports[portIndex].commodities[commodityIndex].buyFor);
            fprintf(file, "\t\t\t\t<sell>%d</sell>\n", gameData.ports[portIndex].commodities[commodityIndex].sellFor);
            fprintf(file, "\t\t\t</commodity>\n");
        }

        fprintf(file, "\t\t</commodities>\n");
        fprintf(file, "\t</port>\n");
    }

    fprintf(file, "</gamedata>\n");
    fclose(file);
}
