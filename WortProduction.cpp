//
// Created by thomas on 23.11.17.
//

#include "WortProduction.h"
using namespace std;

WortProduction::WortProduction(unsigned int bType)
{
    beerType = bType;
}

double WortProduction::MLATO = 0;
double WortProduction::HORKE_KALY = 0;

void WortProduction::Behavior() {

    /** Cleaning **/
    Wait(MALT_MOVE_TIME);

    Enter(ChainConveyor, 1);

    Wait(CHAIN_MOVE_TIME);

    Enter(Magnet, 1);
    Leave(Magnet, 1);

    Enter(DustFilter, 1);
    Leave(DustFilter, 1);

    Leave(ChainConveyor, 1);

    /** Scrapping **/
    Enter(Scraper, 1);

    Wait(Uniform(MIN_SCRAPPING_TIME, MAX_SCRAPPING_TIME));

    Leave(Scraper, 1);

    /** Vystirani a Rmutovani**/
    Enter(VystiraciTub, 1);

    for(int i = 1; i <= 4; i++) {

        CookingWaterStore.get(this, 1);

        Wait(Uniform(MIN_MIX_WATER_TIME, MAX_MIX_WATER_TIME));
    }

    Enter(RmutTub, 1);

    Wait(WARMING_TIME);
    Wait(REST_TIME);
    Wait(WARMING_TIME2);
    Wait(Uniform(MIN_REST_TIME2, MAX_REST_TIME2));
    Wait(WARMING_TIME3);
    Wait(Uniform(MIN_SUGARING_TIME, MAX_SUGARING_TIME));
    Wait(Uniform(MIN_BOIL_TIME, MAX_BOIL_TIME));
    Wait(Uniform(MIN_COOK_TIME, MAX_COOK_TIME));
    Wait(Uniform(MIN_BACK_AND_SUGARING, MAX_BACK_AND_SUGARING));
    Wait(Uniform(MIN_BACK_AND_WAIT, MAX_BACk_AND_WAIT));
    Wait(FINISHING);

    (new TubCleaning(&RmutTub))->Activate();
    (new TubCleaning(&VystiraciTub))->Activate();

    /** Scezovani **/
    Wait(MIXING_AND_PUMP_TIME);

    Enter(ScezovaciTub, 1);

    Wait(PUMPING_TIME);

    CookingWaterStore.get(this, 2);

    Wait(Uniform(MIN_SWEETING_TIME, MAX_SWEETING_TIME));

    (new ScezovaciTubCleaning(beerType))->Activate();

    /** Chmelovar **/

    if(MladinovaPan.Full() || HopStore.isFull()) {
        WaitUntil(!(MladinovaPan.Full()) && !(HopStore.isFull()))
    }

    Enter(MladinovaPan, 1);
    HopStore.get(this, HOP_NEEDED);

    Wait(Uniform(MIN_CHMELOVAR_TIME, MAX_CHMELOVAR_TIME));

    if(HopStore.isFull()) {
        WaitUntil(!(HopStore.isFull()));
    }

    HopStore.get(this, AROMATIC_HOP_NEEDED);


    Wait(SECOND_PHASE);

    (new TubCleaning(&MladinovaPan))->Activate();

    /** Curling **/
    Enter(CurlingTub, 1);

    Wait(Uniform(MIN_SEPARATION_TIME, MAX_SEPARATION_TIME));
    WortProduction::HORKE_KALY += HORKE_KALY_RUBBISH;

    (new TubCleaning(&CurlingTub))->Activate();

    /** Cooling **/
    Enter(WortCooler, 1);
    Wait(COOLING_TIME);
    Leave(WortCooler, 1);


    switch(beerType) {
        case LIGHT_BEER:
            LightBeerWortStore.put(600);
            break;
        case DARK_BEER:
            DarkBeerWortStore.put(600);
            break;
        case LAGER_BEER:
            LagerBeerWortStore.put(600);
            break;
        default:
            break;
    }

}

void WortProduction::PrintRubbishStats()
{
    printf("+-----------------------------------------------------+\n");
    printf("Odpad z produkce mladiny:                             |\n");
    printf("+------------------------------------------------------\n");
    printf("|   Mlato:         %fhl\n", WortProduction::MLATO);
    printf("|   Horke Kaly:    %fkg\n", WortProduction::HORKE_KALY);
    printf("+-----------------------------------------------------+\n");
}

ScezovaciTubCleaning::ScezovaciTubCleaning(unsigned int bType)
{
    beerType = bType;
}

void ScezovaciTubCleaning::Behavior()
{
    switch(beerType) {
        case LIGHT_BEER:
            WortProduction::MLATO += PILSER_MLATO_RUBBISH;
            break;
        case DARK_BEER:
            WortProduction::MLATO += BAVARIAN_MLATO_RUBBISH;
            break;
        case LAGER_BEER:
            WortProduction::MLATO += CARAMEL_MLATO_RUBBISH;
            break;
        default:
            break;
    }

    Wait(CLEAN_TIME);

    Leave(ScezovaciTub, 1);
}

TubCleaning::TubCleaning(Store* fac_name)
{
    fac = fac_name;
}

void TubCleaning::Behavior()
{
    Wait(CLEAN_TIME);

    Leave(*fac, 1);
}