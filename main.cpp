#include <iostream>
#include <simlib.h>
#include <chrono>
#include "MaltProduction.h"
#include "Fermentation.h"
#include "WortProduction.h"
#include "Filtration.h"
#include "CarProcess.h"
#include "MainLine.h"
#include "main.h"

using namespace std;

long int START_TIME = 0;
long int END_TIME = 1 YEAR;

double NEXT_BATCH_TIME = 182 MINUTE;
unsigned int LIGHT_BEER_BATCH_AMOUNT = 3;
unsigned int DARK_BEER_BATCH_AMOUNT = 1;
unsigned int LAGER_BEER_BATCH_AMOUNT = 1;

/* Cooking water in hundreds of hl*/
double WATER_PUMPING_TIME = 10 MINUTE;
const int PUMP_AMOUNT = 1;
const int WATER_CAPACITY = 400;
const int INITIALIZED_WATER_AMOUNT = 50;
MaterialStore CookingWaterStore("Water store", WATER_CAPACITY, INITIALIZED_WATER_AMOUNT, WATER_PUMPING_TIME, PUMP_AMOUNT);

/* Hop in 2 batches for wort batch (one batch is around 50 kg - 20kg of aromatic and 30kg of normal hop)*/
double HOP_FERRY_TIME = 10;
const int HOP_FERRY_AMOUNT = 8;
const int HOP_CAPACITY = 100;
const int INITIALIZED_HOP_AMOUNT = 16;
MaterialStore HopStore("Hop store", HOP_CAPACITY, INITIALIZED_HOP_AMOUNT, HOP_FERRY_TIME, HOP_FERRY_AMOUNT);


/* Yeast in batches for fermentation tub*/
double YEAST_FERRY_TIME = 10;
const int FERRY_AMOUNT = 100;
const int YEAST_CAPACITY = 1000;
const int INITIALIZED_YEAST_AMOUNT = 100;
MaterialStore YeastStore("Yeast store", YEAST_CAPACITY, INITIALIZED_YEAST_AMOUNT, YEAST_FERRY_TIME, FERRY_AMOUNT);




/* Wort in hl*/
const int WORT_CAPACITY = 100*600;
const int INITIALIZED_WORT_AMOUNT = 0;
MaterialHolder LightBeerWortStore(WORT_CAPACITY, INITIALIZED_WORT_AMOUNT, LIGHT_BEER);
MaterialHolder DarkBeerWortStore(WORT_CAPACITY, INITIALIZED_WORT_AMOUNT, DARK_BEER);
MaterialHolder LagerBeerWortStore(WORT_CAPACITY, INITIALIZED_WORT_AMOUNT, LAGER_BEER);

/* Young Beer in 200hl*/
const int YOUNG_BEER_CAPACITY = 100;
const int INITIALIZED_YOUNG_BEER_AMOUNT = 0;
MaterialHolder LightBeerStore(YOUNG_BEER_CAPACITY, INITIALIZED_YOUNG_BEER_AMOUNT, LIGHT_BEER);
MaterialHolder DarkBeerStore(YOUNG_BEER_CAPACITY, INITIALIZED_YOUNG_BEER_AMOUNT, DARK_BEER);
MaterialHolder LagerBeerStore(YOUNG_BEER_CAPACITY, INITIALIZED_YOUNG_BEER_AMOUNT, LAGER_BEER);

/* Malt in batches for 600hl of wort*/
const int MALT_CAPACITY = 800;
const int INITIALIZED_PILSEN_MALT_AMOUNT = 320;
const int INITIALIZED_BAVARIAN_MALT_AMOUNT = 80;
const int INITIALIZED_CARAMEL_MALT_AMOUNT = 80;
MaterialHolder PilsenMaltStore(MALT_CAPACITY, INITIALIZED_PILSEN_MALT_AMOUNT, PILSEN_MALT);
MaterialHolder BavarianMaltStore(MALT_CAPACITY, INITIALIZED_BAVARIAN_MALT_AMOUNT, BAVARIAN_MALT);
MaterialHolder CaramelMaltStore(MALT_CAPACITY, INITIALIZED_CARAMEL_MALT_AMOUNT, CARAMEL_MALT);

/* Malt constants, stores and facilities */
double MALT_GENERATION_TIME = 12.2 MINUTE;

Store Aspirator("Aspirator", 2);
Store ConicalTub("ConicalTub", 3);
unsigned long int CaramelMaltExpedition = 0;
unsigned long int BavarianMaltExpedition = 0;
unsigned long int PilsenMaltExpedition = 0;
Store SaladinTub("SaladinTub", 14);
Store Hvozd("Hvozd", 200);
Store Odklicovacka("Odklicovacka", 2);


/* Wort constants, stores and facilities */
Store ChainConveyor("ChainConveyor", 1);
Store Magnet("Magnet", 1);
Store DustFilter("DustFilter", 1);
Store Scraper("Scraper", 1);
Store VystiraciTub("VystiraciTub", 1);
Store RmutTub("RmutTub", 1);
Store ScezovaciTub("ScezovaciTub", 1);
Store MladinovaPan("MladinovaPan", 1);
Store CurlingTub("CurlingTub", 1);
Store WortCooler("Cooler", 1);


/* Main Fermentation */
Store FermentationTub("FermentationTub", 160);
Store MaturationTub("MaturationTub", 920);


/* Filtration*/
Store Candle_Filter("Candle Filter", 30);
Store Paster("Paster", 2);
Store Bottler("Bottler", 2);

Histogram NumOfPilsenMalt("Histogram mnozstvi na sklade plzenskeho sladu", 0, 80, 10);
Histogram NumOfCaramelMalt("Histogram mnozstvi na sklade karameloveho sladu", 0, 80, 10);
Histogram NumOfBavarianMalt("Histogram mnozstvi na sklade bavorskeho sladu", 0, 80, 10);

unsigned int Bottles_For_Expedition = 0;

/* CarProcess */
Store Ramp("Ramp", 4);

class MaterialGenerator : public Process
{
    void Behavior()
    {
        CookingWaterStore.activate();
        YeastStore.activate();
        HopStore.activate();
    }
};

class ProductionLineInit : public Process
{
    void Behavior()
    {
        (new MainLine(NEXT_BATCH_TIME, LIGHT_BEER_BATCH_AMOUNT, DARK_BEER_BATCH_AMOUNT, LAGER_BEER_BATCH_AMOUNT))->Activate();
        (new Fermentation)->Activate();
        (new Filtration)->Activate();

        for(int i = 1; i <= 60; i++) {
            (new CarProcess)->Activate();
        }
    }
};

class MaltProductionGenerator : public Event
{
    void Behavior()
    {
        (new MaltProduction())->Activate();
        Activate(Time + Exponential(MALT_GENERATION_TIME));
    }
};

void printOutput()
{
    printf("=======================================================\n");
    printf("=======================================================\n");
    printf("|   Statistiky ve skladu sladu:                       |\n");
    printf("+-----------------------------------------------------+\n");
    printf("|   Pilzensky slad:\n");
    PilsenMaltStore.output();
    printf("|   Bavorsky slad:\n");
    BavarianMaltStore.output();
    printf("|   Karamelovy slad:\n");
    CaramelMaltStore.output();
    printf("|   Statistiky ve vyrobe sladu:-------------------------+\n");
    MaltProduction::PrintRubbishStats();
    Aspirator.Output();
    ConicalTub.Output();
    SaladinTub.Output();
    Hvozd.Output();
    Odklicovacka.Output();
    printf("+------------------------------------------------------+\n");
    printf("|   Prodej druhu sladu:                                |\n");
    printf("+------------------------------------------------------+\n");
    printf("|   Prodaný karamelový slad %ft\n", CaramelMaltExpedition*0.86);
    printf("|   Prodaný bavorský slad %ft\n", BavarianMaltExpedition*9.53);
    printf("|   Prodaný plzeňský slad %ft\n", PilsenMaltExpedition*7.7);
    printf("+------------------------------------------------------+\n");
    printf("=======================================================\n");
    printf("=======================================================\n");

    printf("=======================================================\n");
    printf("=======================================================\n");
    printf("|   Statistiky ve skladu mladině:\n");
    printf("|   Mladina svetleho piva:---------------------------------\n");
    LightBeerWortStore.output();
    printf("\n");
    printf("|   Mladina polotmaveho piva:------------------------------\n");
    DarkBeerWortStore.output();
    printf("\n");
    printf("|   Mladina lažáku:----------------------------------------\n");
    LagerBeerWortStore.output();
    printf("-------------------------------------------------------\n");
    printf("|   Statistiky ve vyrobe mladiny:\n");
    WortProduction::PrintRubbishStats();
    ChainConveyor.Output();
    Scraper.Output();
    VystiraciTub.Output();
    RmutTub.Output();
    ScezovaciTub.Output();
    MladinovaPan.Output();
    CurlingTub.Output();
    WortCooler.Output();
    printf("=======================================================\n");
    printf("=======================================================\n");

    printf("=======================================================\n");
    printf("=======================================================\n");
    printf("|   Statistiky ve skladu piva pred expedici:           |\n");
    printf("|------------------------------------------------------|\n");
    MainLine::PrintBeerAmount();
    printf("|   Pilzenske pivo:                                    |\n");
    printf("|------------------------------------------------------|\n");
    LightBeerStore.output();
    printf("-------------------------------------------------------\n");
    printf("|   Polotmave pivo:                                   |\n");
    printf("-------------------------------------------------------\n");
    DarkBeerStore.output();
    printf("-------------------------------------------------------\n");
    printf("|   Lezacke pivo:                                     |\n");
    printf("-------------------------------------------------------\n");
    LagerBeerStore.output();
    printf("=======================================================\n");
    printf("=======================================================\n");


    printf("=======================================================\n");
    printf("=======================================================\n");
    printf("Statistiky při zrání\n");
    FermentationTub.Output();
    MaturationTub.Output();
    printf("=======================================================\n");
    printf("=======================================================\n");


    printf("=======================================================\n");
    printf("=======================================================\n");
    printf("Statistiky při filtraci:\n");
    Candle_Filter.Output();
    Paster.Output();
    Bottler.Output();
    printf("=======================================================\n");
    printf("=======================================================\n");

    printf("=======================================================\n");
    printf("=======================================================\n");
    CarProcess::PrintInfoAboutExpedition();
    printf("=======================================================\n");
    printf("=======================================================\n");

    printf("+------------------------------------------------------\n");
    printf("|  Ve stovkách hl\n");
    CookingWaterStore.output();

    printf("+------------------------------------------------------\n");
    printf("|  V hl\n");
    YeastStore.output();

    printf("+------------------------------------------------------\n");
    printf("|  V 25kg\n");
    HopStore.output();

    NumOfPilsenMalt.Output();
    NumOfCaramelMalt.Output();
    NumOfBavarianMalt.Output();


}


void argumentsHandle(int argc, char **argv)
{
    if(argc < 2) {
        return;
    }
    if(argv[1][0] == '-' && argv[1][1] == 'h') {
        printf("Simulation of brewery help:\n");
        printf("Arguments have to be in order -h or first three or all");
        printf("./pivovar [-h] [END_TIME] [NEXT_BATCH_TIME] [MALT_GENERATION_TIME] [WATER_PUMPING_TIME] [HOP_FERRY_TIME] [YEAST_FERRY_TIME]\n");
        printf("-h - prints this help\n");
        printf("END_TIME - simulation end time (year)\n");
        printf("NEXT_BATCH_TIME - time when the new batch starts (h)\n");
        printf("MALT_GENERATION_TIME - time when the malt ferry comes (min)\n");
        printf("WATER_PUMPING_TIME - water pumping time (100hl)\n");
        printf("HOP_FERRY_TIME - hop ferry time (h)\n");
        printf("YEAST_FERRY_TIME - yeast ferry time (h)\n");
        exit(0);
    }
    if(argc < 3) {
        printf("Wrong arguments, for more information write -h\n");
        exit(1);
    }

    if(argc == 4) {
        END_TIME = std::atol(argv[1]) YEAR;
        NEXT_BATCH_TIME = std::atol(argv[2]);
        MALT_GENERATION_TIME = std::atol(argv[3]) MINUTE;
        return;
    }
    else if(argc > 4 && argc < 7 && argc > 7) {
        printf("Wrong arguments, for more information write -h\n");
        exit(1);
    }
    else {
        END_TIME = std::atol(argv[1]) YEAR;
        NEXT_BATCH_TIME = std::atol(argv[2]);
        MALT_GENERATION_TIME = std::atol(argv[3]) MINUTE;
        WATER_PUMPING_TIME = std::atol(argv[4]);
        HOP_FERRY_TIME = std::atol(argv[5]);
        YEAST_FERRY_TIME = std::atol(argv[6]);
    }
}

int main(int argc, char** argv) {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    RandomSeed(seed);

    argumentsHandle(argc, argv);

    Init(START_TIME, END_TIME);

    (new MaterialGenerator)->Activate();

    (new ProductionLineInit)->Activate();

    (new MaltProductionGenerator)->Activate();

    Run();

    printOutput();

    return 0;
}

