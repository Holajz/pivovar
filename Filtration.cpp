//
// Created by thomas on 24.11.17.
//

#include "Filtration.h"
using namespace std;

void Filtration::Behavior()
{
    while(1) {
        if(LightBeerStore.hasMaterial(1)) {
            LightBeerStore.get(1);
            (new FiltrationAndPasterization)->Activate();
        }
        else if(DarkBeerStore.hasMaterial(1)) {
            DarkBeerStore.get(1);
            (new FiltrationAndPasterization)->Activate();
        }
        else if(LagerBeerStore.hasMaterial(1)) {
            LagerBeerStore.get(1);
            (new FiltrationAndPasterization)->Activate();
        }

        WaitUntil(LightBeerStore.hasMaterial(1) || DarkBeerStore.hasMaterial(1) || LagerBeerStore.hasMaterial(1));
    }
}

unsigned int FiltrationAndPasterization::BatchAmount = 0;

void FiltrationAndPasterization::Behavior()
{
    Enter(Candle_Filter, 1);
    Wait(Uniform(MIN_FILTRATION_TIME, MAX_FILTRATION_TIME));
    Leave(Candle_Filter, 1);

    Enter(Paster, 1);
    Wait(PASTERIZATION_TIME);
    Leave(Paster, 1);

    FiltrationAndPasterization::BatchAmount++;

    if(FiltrationAndPasterization::BatchAmount >= BATCH_AMOUNT_TO_START) {
        for(unsigned int i = 1; i <= FiltrationAndPasterization::BatchAmount; i++) {
            (new Bottling)->Activate();
        }
        FiltrationAndPasterization::BatchAmount = 0;
    }
    else {
        return;
    }

}

void Bottling::Behavior()
{

    Enter(Bottler, 1);
    Wait(BOTTLING_TIME);
    Leave(Bottler, 1);

    Bottles_For_Expedition += BOTTLE_PER_TUB;

}
