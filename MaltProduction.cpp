//
// Created by thomas on 24.11.17.
//

#include "MaltProduction.h"
using namespace std;

double Uskladneni::BAVARIAN_MALT_WAIT = 0;
double Uskladneni::PILSEN_MALT_WAIT = 0;
double Uskladneni::CARAMEL_MALT_WAIT = 0;
double Uskladneni::SLAD_BLOOM = 0;

void Maceni::Behavior()
{

    MaltProduction::NUM_FOR_CONICAL_TUB = 0;

    Enter(ConicalTub, 1);

    CookingWaterStore.get(this, 25);

    Wait(Uniform(MIN_MACENI_TIME, MAX_MACENI_TIME));

    MaltProduction::MACECI_WATER_AMOUNT += 18;

    Leave(ConicalTub, 1);

    for(unsigned int i = 1; i <= NUM_CONICAL_CREATED; i++) {
        (new Kliceni)->Activate();
    }
    Terminate();
}

void Kliceni::Behavior()
{

    if(Random() <= RUBBISH_FROM_MACENI) {
        MaltProduction::MACECI_RUBBISH_AMOUNT++;
        return;
    }

    /** Kliceni **/
    MaltProduction::NUM_FOR_SALADIN_TUB++;

    if(MaltProduction::NUM_FOR_SALADIN_TUB == NUM_FOR_SALADIN_NEEDED) {

        (new Kliceni_Process)->Activate();
    }
}


void Kliceni_Process::Behavior() {
    MaltProduction::NUM_FOR_SALADIN_TUB = 0;

    Enter(SaladinTub, 1);

    Wait(SUCHA_HROMADA_TIME);
    Wait(PROVZDUSNOVANI_TIME);
    Wait(OBRACENI_A_KROPENI_TIME);

    Leave(SaladinTub, 1);

    for(unsigned int i = 1; i <= NUM_ZELENY_SLAD_CREATED; i++) {
        (new Hvozdeni)->Activate();
    }
}

unsigned int Hvozdeni::NUM_FOR_CARAMEL = 0;
unsigned int Hvozdeni::NUM_FOR_BAVARIAN = 0;
unsigned int Hvozdeni::NUM_FOR_PILSEN = 0;

void Hvozdeni::Behavior()
{

    Enter(Hvozd, 1);

    double rand_value = Random();

    if(rand_value <= CARAMEL_PROCESS) {
        Hvozdeni::NUM_FOR_CARAMEL++;

        if(Hvozdeni::NUM_FOR_CARAMEL == CARAMEL_NUM_NEEDED_FOR_START) {
            Hvozdeni::NUM_FOR_CARAMEL -= 10;
            (new Hvozdeni_Process(CARAMEL_MALT))->Activate();
        }
    }
    else if(rand_value > CARAMEL_PROCESS && rand_value <= BAVARIAN_PROCESS) {
        Hvozdeni::NUM_FOR_BAVARIAN++;

        if(Hvozdeni::NUM_FOR_BAVARIAN == BAVARIAN_NUM_NEEDED_FOR_START) {
            Hvozdeni::NUM_FOR_BAVARIAN -= 10;
            (new Hvozdeni_Process(BAVARIAN_MALT))->Activate();
        }
    }
    else {
        Hvozdeni::NUM_FOR_PILSEN++;

        if(Hvozdeni::NUM_FOR_PILSEN == PILSEN_NUM_NEEDED_FOR_START) {
            Hvozdeni::NUM_FOR_PILSEN -= 10;
            (new Hvozdeni_Process(PILSEN_MALT))->Activate();
        }
    }

}

Hvozdeni_Process::Hvozdeni_Process(unsigned int m_type)
{
    Malt_type = m_type;
}

void Hvozdeni_Process::Behavior()
{

    switch(Malt_type) {
        case CARAMEL_MALT:
            Wait(PREDSUSENI_c);
            Wait(VYHRATI_c);
            Wait(DOTAHOVANI_c);
            break;
        case BAVARIAN_MALT:
            Wait(PREDSUSENI);
            Wait(VYHRATI);
            Wait(DOTAHOVANI);
            break;
        case PILSEN_MALT:
            Wait(SUSENI);
            Wait(SUSENI);
            break;
    }

    Leave(Hvozd, 10);

    Enter(Odklicovacka, 1);
    Wait(ODKLICOVAN_TIME);
    Leave(Odklicovacka, 1);

    for(int i = 1; i <= NUM_DRIED_SLAD_CREATED; i++) {
        (new Uskladneni(Malt_type))->Activate();
    }
}

void Uskladneni::Behavior()
{
    Uskladneni::SLAD_BLOOM += 40;

    switch(Malt_type) {
        case CARAMEL_MALT:
        {
            Uskladneni::CARAMEL_MALT_WAIT++;

            if(CARAMEL_MALT_NEEDED <= Uskladneni::CARAMEL_MALT_WAIT) {
                Uskladneni::CARAMEL_MALT_WAIT -= CARAMEL_MALT_NEEDED;
                Wait(Uniform(MIN_USKLADNENI_TIME, MAX_USKLADNENI_TIME));
                CaramelMaltStore.put(1);

                if(CaramelMaltStore.isMaxCapacity()) {
                    for(unsigned int i = 1; i < CaramelMaltStore.Capacity(); i++) {
                        if(Random() >= GO_EXPEDITION) {
                            CaramelMaltStore.Sell(1);
                            CaramelMaltExpedition++;
                        }
                    }
                }
            }
            break;
        }

        case BAVARIAN_MALT:
        {
            Uskladneni::BAVARIAN_MALT_WAIT++;

            if(BAVARIAN_MALT_NEEDED <= Uskladneni::BAVARIAN_MALT_WAIT) {
                Uskladneni::BAVARIAN_MALT_WAIT -= BAVARIAN_MALT_NEEDED;
                Wait(Uniform(MIN_USKLADNENI_TIME, MAX_USKLADNENI_TIME));
                BavarianMaltStore.put(1);

                if(BavarianMaltStore.isMaxCapacity()) {
                    for(unsigned int i = 1; i < BavarianMaltStore.Capacity(); i++) {
                        if(Random() >= GO_EXPEDITION) {
                            BavarianMaltStore.Sell(1);
                            BavarianMaltExpedition++;
                        }
                    }
                }
            }
            break;
        }

        case PILSEN_MALT:
        {
            Uskladneni::PILSEN_MALT_WAIT++;

            if(PILSEN_MALT_NEEDED <= Uskladneni::PILSEN_MALT_WAIT) {
                Uskladneni::PILSEN_MALT_WAIT -= PILSEN_MALT_NEEDED;
                Wait(Uniform(MIN_USKLADNENI_TIME, MAX_USKLADNENI_TIME));
                PilsenMaltStore.put(1);
            }
            if(PilsenMaltStore.isMaxCapacity()) {
                for(unsigned int i = 1; i < PilsenMaltStore.Capacity(); i++) {
                    if(Random() >= GO_EXPEDITION) {
                        PilsenMaltStore.Sell(1);
                        PilsenMaltExpedition++;
                    }
                }
            }

            break;
        }
        default:
            break;
    }
}

Uskladneni::Uskladneni(unsigned int type)
{
    Malt_type = type;
}

unsigned int MaltProduction::BACK_BARLEY_AMOUNT = 0;
unsigned int MaltProduction::MACECI_RUBBISH_AMOUNT = 0;
unsigned int MaltProduction::MACECI_WATER_AMOUNT = 0;

unsigned int MaltProduction::NUM_FOR_CONICAL_TUB = 0;
unsigned int MaltProduction::NUM_FOR_SALADIN_TUB = 0;

void MaltProduction::Behavior() {


    /** Cleaning and sorting **/
    Enter(Aspirator, 1);
    Wait(CLEANING_TIME);

    if(Random()<= BACK_BARLEY_SORT) {
        Leave(Aspirator, 1);
        MaltProduction::BACK_BARLEY_AMOUNT++;
        return;
    }
    Leave(Aspirator, 1);


    /** Maceni **/
    MaltProduction::NUM_FOR_CONICAL_TUB++;

    if(MaltProduction::NUM_FOR_CONICAL_TUB == NUM_FOR_CONICAL_NEEDED) {

        (new Maceni)->Activate();
    }
}

void MaltProduction::PrintRubbishStats()
{
    printf("+-----------------------------------------------------+\n");
    printf("|   Odpad z produkce sladu:                           |\n");
    printf("+------------------------------------------------------\n");
    printf("|   Výčist:         %ukg\n", MaltProduction::BACK_BARLEY_AMOUNT*1000);
    printf("|   Odpad z máčení: %ukg\n", MaltProduction::MACECI_RUBBISH_AMOUNT*1000);
    printf("|   Máčecí voda:    %uhl\n", MaltProduction::MACECI_WATER_AMOUNT*100);
    printf("|   Sladový květ:   %fkg\n", Uskladneni::SLAD_BLOOM);
    printf("+-----------------------------------------------------+\n");
    printf("\n\n");
}
