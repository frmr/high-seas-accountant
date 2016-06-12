#define NUM_OF_COMMODITIES  15
#define NUM_OF_PORTS        62

enum hsaCommodityType
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
};

typedef struct hsaCommodity
{
    hsaCommodityType    type;
    int                 quantity;
    int                 buyFor;
    int                 sellFor;
};

typedef struct hsaPort
{
    char*           name;
    hsaCommodity    commodites[NUM_OF_COMMODITIES];
};

typedef struct hsaGameData
{
    int         gold;
    char*       playerName;
    char*       shipName;
    hsaPort     ports[NUM_OF_PORTS];
};

hsaGameData hsaLoadFile(const char* filename)
{
    hasGameData gameData;
    
    //load file
    //jump to 1878
    //for each port
    //  read name
    //      for each commodity
    //          read quantity
    //      for each commodity
    //          read buy price
    //          calculate sell price
    //
    //jump to 973f
    //read gold
    //read player name
    //read ship name
    
    return gameData;
}

void hsaToCsv(const char* filename)
{
    
}