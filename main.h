//
// Created by thomas on 23.11.17.
//

#ifndef IMS_PROJ_MAIN_H
#define IMS_PROJ_MAIN_H

#include "MaterialGenerator.h"
#include "MaterialHolder.h"

#define DEBUG 1

/* Basic time unit will be hours*/
#define SECOND *0.01666666666666*0.01666666666666
#define MINUTE *0.01666666666666
#define DAY *24
#define WEEK *24*7
#define MONTH *24*7*4
#define YEAR *24*7*4*12

/*Material types*/
#define LIGHT_BEER 0
#define DARK_BEER 1
#define LAGER_BEER 2
#define PILSEN_MALT 3
#define BAVARIAN_MALT 4
#define CARAMEL_MALT 5

extern MaterialStore CookingWaterStore;
extern MaterialStore HopStore;
extern MaterialStore YeastStore;

extern MaterialHolder LightBeerWortStore;
extern MaterialHolder DarkBeerWortStore;
extern MaterialHolder LagerBeerWortStore;

extern MaterialHolder LightBeerStore;
extern MaterialHolder DarkBeerStore;
extern MaterialHolder LagerBeerStore;

extern MaterialHolder PilsenMaltStore;
extern MaterialHolder BavarianMaltStore;
extern MaterialHolder CaramelMaltStore;

extern Store Aspirator;
extern Store ConicalTub;
extern unsigned long int CaramelMaltExpedition;
extern unsigned long int BavarianMaltExpedition;
extern unsigned long int PilsenMaltExpedition;
extern Store SaladinTub;
extern Store Hvozd;
extern Store Odklicovacka;

extern Store ChainConveyor;
extern Store Magnet;
extern Store DustFilter;
extern Store Scraper;
extern Store VystiraciTub;
extern Store RmutTub;
extern Store ScezovaciTub;
extern Store MladinovaPan;
extern Store CurlingTub;
extern Store WortCooler;

extern Store FermentationTub;
extern Store MaturationTub;

extern Store Candle_Filter;
extern Store Paster;
extern Store Bottler;

extern unsigned int Bottles_For_Expedition;
extern Store Ramp;

extern Histogram NumOfPilsenMalt;
extern Histogram NumOfCaramelMalt;
extern Histogram NumOfBavarianMalt;


void argumentsHandle(int argc, char **pString);



#endif //IMS_PROJ_MAIN_H
