//
// Created by thomas on 23.11.17.
//

#include <cstdio>
#include "MainLine.h"
using namespace std;

unsigned int MainLine::lightBeerAmount = 0;
unsigned int MainLine::darkBeerAmount = 0;
unsigned int MainLine::lagerBeerAmount = 0;

MainLine::MainLine(double nextBatch, unsigned int lightBBAmount, unsigned int darkBBAmount,
                   unsigned int lagerBBAmount)
{
    NEXT_BATCH_TIME = nextBatch;

    lightBeerBatchAmount = new Store(lightBBAmount);
    darkBeerBatchAmount = new Store(darkBBAmount);
    lagerBeerBatchAmount = new Store(lagerBBAmount);

    lightBatchRepeatAmount = lightBBAmount;
    darkBatchRepeatAmount = darkBBAmount;
    lagerBatchRepeatAmount = lagerBBAmount;

    MainLine::lightBeerAmount = 0;
    MainLine::darkBeerAmount = 0;
    MainLine::lagerBeerAmount = 0;

}

void MainLine::Behavior()
{
    lightBeerBatchAmount->Enter(this, lightBatchRepeatAmount);
    darkBeerBatchAmount->Enter(this, darkBatchRepeatAmount);
    lagerBeerBatchAmount->Enter(this, lagerBatchRepeatAmount);

    while(1) {

        lightBeerBatchAmount->Leave(lightBatchRepeatAmount);

        while(!lightBeerBatchAmount->Full()) {

            lightBeerBatchAmount->Enter(this, 1);

            if(!PilsenMaltStore.hasMaterial(1)) {
                WaitUntil(PilsenMaltStore.hasMaterial(1));
            }

            PilsenMaltStore.get(1);

            NumOfPilsenMalt(PilsenMaltStore.Amount());

            (new WortProduction(LIGHT_BEER))->Activate();

            MainLine::lightBeerAmount++;

            Wait(NEXT_BATCH_TIME);
        }

        darkBeerBatchAmount->Leave(darkBatchRepeatAmount);


        while(!darkBeerBatchAmount->Full()) {
            darkBeerBatchAmount->Enter(this, 1);

            if(!(PilsenMaltStore.hasMaterial(1) && CaramelMaltStore.hasMaterial(1))) {
                WaitUntil(PilsenMaltStore.hasMaterial(1) && CaramelMaltStore.hasMaterial(1));
            }

            PilsenMaltStore.get(1);
            CaramelMaltStore.get(1);

            NumOfCaramelMalt(CaramelMaltStore.Amount());

            NumOfPilsenMalt(PilsenMaltStore.Amount());

            (new WortProduction(DARK_BEER))->Activate();

            MainLine::darkBeerAmount++;

            Wait(NEXT_BATCH_TIME);
        }

        lagerBeerBatchAmount->Leave(lagerBatchRepeatAmount);

        while(!lagerBeerBatchAmount->Full()){
            lagerBeerBatchAmount->Enter(this, 1);

            if(!BavarianMaltStore.hasMaterial(1)) {
                WaitUntil(BavarianMaltStore.hasMaterial(1));
            }

            BavarianMaltStore.get(1);

            NumOfBavarianMalt(BavarianMaltStore.Amount());


            (new WortProduction(LAGER_BEER))->Activate();

            MainLine::lagerBeerAmount++;

            Wait(NEXT_BATCH_TIME);
        }

    }

}

void MainLine::PrintBeerAmount()
{
    printf("+-----------------------------------------------------+\n");
    printf("|   Amount of batches                                 |\n");
    printf("+-----------------------------------------------------+\n");
    printf("|   Light beer batch amount: %d\n", MainLine::lightBeerAmount);
    printf("|   Dark beer batch amount:  %d\n", MainLine::darkBeerAmount);
    printf("|   Lager beer batch amount: %d\n", MainLine::lagerBeerAmount);
    printf("+-----------------------------------------------------+\n");
}
