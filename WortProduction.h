//
// Created by thomas on 23.11.17.
//

#ifndef IMS_PROJ_WORTPRODUCTION_H
#define IMS_PROJ_WORTPRODUCTION_H

#include <simlib.h>
#include "main.h"

class WortProduction : public Process
{
private:

    unsigned int beerType;

    const double MALT_MOVE_TIME = 10 MINUTE;
    const double CHAIN_MOVE_TIME = 20 MINUTE;

    const double MIN_SCRAPPING_TIME = 60 MINUTE;
    const double MAX_SCRAPPING_TIME = 90 MINUTE;

    const double MIN_MIX_WATER_TIME = 3 MINUTE;
    const double MAX_MIX_WATER_TIME = 5 MINUTE;

    const double WARMING_TIME = 15 MINUTE;
    const double REST_TIME = 10 MINUTE;
    const double WARMING_TIME2 = 11 MINUTE;
    const double MIN_REST_TIME2 = 10 MINUTE;
    const double MAX_REST_TIME2 = 20 MINUTE;
    const double WARMING_TIME3 = 12 MINUTE;
    const double MIN_SUGARING_TIME = 5 MINUTE;
    const double MAX_SUGARING_TIME = 10 MINUTE;
    const double MIN_BOIL_TIME = 10 MINUTE;
    const double MAX_BOIL_TIME = 15 MINUTE;
    const double MIN_COOK_TIME = 15 MINUTE;
    const double MAX_COOK_TIME = 20 MINUTE;
    const double MIN_BACK_AND_SUGARING = 20 MINUTE;
    const double MAX_BACK_AND_SUGARING = 25 MINUTE;
    const double MIN_BACK_AND_WAIT = 20 MINUTE;
    const double MAX_BACk_AND_WAIT = 25 MINUTE;
    const double FINISHING = 10 MINUTE;

    const double PUMPING_TIME = 10 MINUTE;
    const double MIN_SWEETING_TIME = 100 MINUTE;
    const double MAX_SWEETING_TIME = 130 MINUTE;

    const double MIXING_AND_PUMP_TIME = 10 MINUTE;

    const double MIN_CHMELOVAR_TIME = 60 MINUTE;
    const double MAX_CHMELOVAR_TIME = 120 MINUTE;
    const double SECOND_PHASE = 20 MINUTE;

    const double MIN_SEPARATION_TIME = 30 MINUTE;
    const double MAX_SEPARATION_TIME = 45 MINUTE;

    const double COOLING_TIME = 60 MINUTE;

    const unsigned int AROMATIC_HOP_NEEDED = 1;
    const unsigned int HOP_NEEDED = 1;

    /* Rubbish amount */
    //in kg
    const unsigned int HORKE_KALY_RUBBISH = 480;



public:
    /* Rubbish */
    static double MLATO; //in hl
    static double HORKE_KALY; //in kg

    explicit WortProduction(unsigned int bType);

    void Behavior();

    static void PrintRubbishStats();

};

class ScezovaciTubCleaning : public Process
{
private:
    unsigned int beerType;

    const double CLEAN_TIME = 8 MINUTE;

    /* Rubbish amount */
    //in hl
    const double PILSER_MLATO_RUBBISH = 93.24;
    const double BAVARIAN_MLATO_RUBBISH = 114.36;
    const double CARAMEL_MLATO_RUBBISH = 103.56;

public:
    explicit ScezovaciTubCleaning(unsigned int bType);

    void Behavior();

};


class TubCleaning : public Process
{
private:
    Store* fac;

    const double CLEAN_TIME = 8 MINUTE;

public:
    explicit TubCleaning(Store* fac_name);

    void Behavior();

};


#endif //IMS_PROJ_WORTPRODUCTION_H
