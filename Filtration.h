//
// Created by thomas on 24.11.17.
//

#ifndef IMS_PROJ_FILTRATIONANDEXPEDITION_H
#define IMS_PROJ_FILTRATIONANDEXPEDITION_H

#include <simlib.h>
#include "main.h"



class Filtration : public Process
{
public:
    void Behavior();
};

class FiltrationAndPasterization : public Process
{
private:
    const double MIN_FILTRATION_TIME = 18;
    const double MAX_FILTRATION_TIME = 30;
    const double PASTERIZATION_TIME = 1;

    const unsigned int BATCH_AMOUNT_TO_START = 4;

public:
    static unsigned int BatchAmount;

    void Behavior();
};

class Bottling :public Process
{
private:
    const double BOTTLING_TIME = 65 MINUTE;
    const unsigned int BOTTLE_PER_TUB = 40000;
public:
    void Behavior();
};


#endif //IMS_PROJ_FILTRATIONANDEXPEDITION_H
