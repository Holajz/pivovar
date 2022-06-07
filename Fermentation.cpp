//
// Created by thomas on 23.11.17.
//

#include "Fermentation.h"
using namespace std;

unsigned int Fermentation::Yeast = 0;

void Fermentation::Behavior() {
    while(1) {
        if(LightBeerWortStore.hasMaterial(200)) {
            LightBeerWortStore.get(200);
            (new Fermentation_Process(LIGHT_BEER))->Activate();
        }
        else if(DarkBeerWortStore.hasMaterial(200)) {
            DarkBeerWortStore.get(200);
            (new Fermentation_Process(DARK_BEER))->Activate();
        }
        else if(LagerBeerWortStore.hasMaterial(200)) {
            LagerBeerWortStore.get(200);
            (new Fermentation_Process(LAGER_BEER))->Activate();
        }

        WaitUntil(LightBeerWortStore.hasMaterial(200) || DarkBeerWortStore.hasMaterial(200) || LagerBeerWortStore.hasMaterial(200));
    }
}

Fermentation_Process::Fermentation_Process(unsigned int bType) {
    beerType = bType;
}

void Fermentation_Process::Behavior() {

    Enter(FermentationTub, 1);

    Wait(PUMP_TIME);

    YeastStore.get(this, 7);


    Wait(FERMENTATION_TIME);
    Wait(Uniform(MIN_CREAM_WHITE_FOAM_TIME, MAX_CREAM_WHITE_FOAM_TIME));
    Wait(Uniform(MIN_BROWNING_FOAM_TIME, MAX_BROWNING_FOAM_TIME));
    Wait(Uniform(MIN_BLANKET_CREATION_TIME, MAX_BLANKET_CREATION_TIME));
    Wait(Uniform(MIN_YEAST_ON_THE_BOTTOM_TIME, MAX_YEAST_ON_THE_BOTTOM_TIME));

    Leave(FermentationTub, 1);
    Fermentation::Yeast += 7;

    switch(beerType) {
        case LIGHT_BEER:
            Enter(MaturationTub, 1);
            Wait(Uniform(MIN_LIGHT_BEER_MATURATION_TIME, MAX_LIGHT_BEER_MATURATION_TIME));
            Leave(MaturationTub, 1);
            LightBeerStore.put(1);
            break;
        case DARK_BEER:
            Enter(MaturationTub, 1);
            Wait(Uniform(MIN_DARK_BEER_MATURATION_TIME, MAX_DARK_BEER_MATURATION_TIME));
            Leave(MaturationTub, 1);
            DarkBeerStore.put(1);
            break;
        case LAGER_BEER:
            Enter(MaturationTub, 1);
            Wait(Uniform(MIN_LAGER_BEER_MATURATION_TIME, MAX_LAGER_BEER_MATURATION_TIME));
            Leave(MaturationTub, 1);
            LagerBeerStore.put(1);
            break;
        default:
            break;
    }

}
