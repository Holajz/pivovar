//
// Created by thomas on 23.11.17.
//

#ifndef IMS_PROJ_FERMENTATION_H
#define IMS_PROJ_FERMENTATION_H

#include <simlib.h>
#include "main.h"




class Fermentation : public Process
{
private:
public:
    /* Rubbish yeast */
    static unsigned int Yeast; //in hl
    void Behavior();
};

class Fermentation_Process : public Process
{
private:
    unsigned int beerType;

    const double PUMP_TIME = 20 MINUTE;
    const double FERMENTATION_TIME = 12;
    const double MIN_CREAM_WHITE_FOAM_TIME = 12;
    const double MAX_CREAM_WHITE_FOAM_TIME = 16;
    const double MIN_BROWNING_FOAM_TIME = 2 DAY;
    const double MAX_BROWNING_FOAM_TIME = 3 DAY;
    const double MIN_BLANKET_CREATION_TIME = 24;
    const double MAX_BLANKET_CREATION_TIME = 36;
    const double MIN_YEAST_ON_THE_BOTTOM_TIME = 12;
    const double MAX_YEAST_ON_THE_BOTTOM_TIME = 24;


    const double MIN_LIGHT_BEER_MATURATION_TIME = 15 DAY;
    const double MAX_LIGHT_BEER_MATURATION_TIME = 25 DAY;

    const double MIN_DARK_BEER_MATURATION_TIME = 40 DAY;
    const double MAX_DARK_BEER_MATURATION_TIME = 50 DAY;

    const double MIN_LAGER_BEER_MATURATION_TIME = 70 DAY;
    const double MAX_LAGER_BEER_MATURATION_TIME = 90 DAY;


public:
    explicit Fermentation_Process(unsigned int bType);

    void Behavior();
};


#endif //IMS_PROJ_FERMENTATION_H
