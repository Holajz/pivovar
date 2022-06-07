

#ifndef IMS_PROJ_MALTPRODUCTION_H
#define IMS_PROJ_MALTPRODUCTION_H

#include <simlib.h>
#include "main.h"


class Maceni : public Process
{
private:

    double MIN_MACENI_TIME = 24;
    double MAX_MACENI_TIME = 36;

    const unsigned int NUM_CONICAL_CREATED = 50;

public:

    void Behavior();
};

class Kliceni : public Process
{
private:

    const double RUBBISH_FROM_MACENI = 0.02;
    const unsigned int NUM_FOR_SALADIN_NEEDED = 40;

public:

    void Behavior();
};

class Kliceni_Process : public Process
{
private:

    double SUCHA_HROMADA_TIME = 24;
    double PROVZDUSNOVANI_TIME = 24;
    double OBRACENI_A_KROPENI_TIME = 84;

    const unsigned int NUM_ZELENY_SLAD_CREATED = 56;

public:

    void Behavior();
};

class Hvozdeni : public Process
{
private:

    const double BAVARIAN_PROCESS = 0.27;
    const double CARAMEL_PROCESS = 0.02;

    const unsigned int CARAMEL_NUM_NEEDED_FOR_START = 10;
    const unsigned int BAVARIAN_NUM_NEEDED_FOR_START = 10;
    const unsigned int PILSEN_NUM_NEEDED_FOR_START = 10;

    static unsigned int NUM_FOR_CARAMEL;
    static unsigned int NUM_FOR_BAVARIAN;
    static unsigned int NUM_FOR_PILSEN;

public:

    void Behavior();
};

class Hvozdeni_Process : public Process
{
private:
    unsigned int Malt_type;

    /* Bavarian */
    const double PREDSUSENI = 30;
    const double VYHRATI = 6;
    const double DOTAHOVANI = 4;

    /* Pilsen */
    const double SUSENI = 12;

    /* Caramel */
    const double PREDSUSENI_c = 40;
    const double VYHRATI_c = 4;
    const double DOTAHOVANI_c = 2;

    const double DEFAULT_WAIT = 20;

    /* Odklicovani */
    const double ODKLICOVAN_TIME = 10 MINUTE;

    const int NUM_DRIED_SLAD_CREATED = 8;
public:
    void Behavior();

    Hvozdeni_Process(unsigned int m_type);
};

class Uskladneni : public Process
{
private:
    unsigned int Malt_type;

    const double MIN_USKLADNENI_TIME = 20 MINUTE;
    const double MAX_USKLADNENI_TIME = 40 MINUTE;

    const double BAVARIAN_MALT_NEEDED = 9.53;
    const double PILSEN_MALT_NEEDED = 7.70;
    const double CARAMEL_MALT_NEEDED = 0.86;

    static double BAVARIAN_MALT_WAIT;
    static double PILSEN_MALT_WAIT;
    static double CARAMEL_MALT_WAIT;

    double GO_EXPEDITION = 0.2;


public:
    /* Rubbish */
    static double SLAD_BLOOM; //in 1000 kilograms

    explicit Uskladneni(unsigned int type);

    void Behavior();
};

class MaltProduction : public Process
{
private:

    /*Cleaning and sorting*/
    const double CLEANING_TIME = 15 MINUTE;
    const double BACK_BARLEY_SORT = 0.04;

    /* Maceni */
    const unsigned int NUM_FOR_CONICAL_NEEDED = 50;


public:

    /* Rubbish */
    static unsigned int BACK_BARLEY_AMOUNT;      //in 1000 kilograms
    static unsigned int MACECI_RUBBISH_AMOUNT;   //in 1000 kilograms
    static unsigned int MACECI_WATER_AMOUNT;     //in hundreds of hl

    /* Maceni */
    static unsigned int NUM_FOR_CONICAL_TUB;

    /* Kliceni */
    static unsigned int NUM_FOR_SALADIN_TUB;

    void Behavior();

    static void PrintRubbishStats();

};




#endif //IMS_PROJ_MALTPRODUCTION_H
