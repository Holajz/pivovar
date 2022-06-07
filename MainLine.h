//
// Created by thomas on 23.11.17.
//

#ifndef IMS_PROJ_RIDICILINKA_H
#define IMS_PROJ_RIDICILINKA_H

#include <simlib.h>
#include "main.h"
#include "WortProduction.h"

class MainLine : public Process{
private:
    double NEXT_BATCH_TIME;
    Store* lightBeerBatchAmount;
    Store* darkBeerBatchAmount;
    Store* lagerBeerBatchAmount;

    unsigned int lightBatchRepeatAmount;
    unsigned int darkBatchRepeatAmount;
    unsigned int lagerBatchRepeatAmount;

public:
    static unsigned int lightBeerAmount;
    static unsigned int darkBeerAmount;
    static unsigned int lagerBeerAmount;


    MainLine(double nextBatch, unsigned int lightBBAmount, unsigned int darkBBAmount, unsigned int lagerBBAmount);

    void Behavior();

    static void PrintBeerAmount();
};


#endif //IMS_PROJ_RIDICILINKA_H
