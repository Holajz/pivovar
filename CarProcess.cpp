//
// Created by thomas on 24.11.17.
//

#include "CarProcess.h"
using namespace std;

unsigned int CarProcess::LoadAmount = 0;
double CarProcess::LoadTime = 0;
unsigned int CarProcess::UsedCars = 0;

void CarProcess::Behavior()
{
    while(1) {
        if(Ramp.Full()) {
            WaitUntil(!Ramp.Full());
        }


        double time = Time;

        Enter(Ramp, 1);

        UsedCars++;

        for(unsigned int i = 1; i < CAR_CAPACITY; i++) {
            WaitUntil(Bottles_For_Expedition > LOAD_AMOUNT);
            Bottles_For_Expedition -= LOAD_AMOUNT;
            Wait(LOADING_TIME);
        }

        CarProcess::LoadTime += Time - time;
        CarProcess::LoadAmount++;

        Leave(Ramp, 1);

        Wait(Uniform(MIN_TRANSPORT_TIME, MAX_TRANSPORT_TIME));

        UsedCars--;
    }

}

void CarProcess::PrintInfoAboutExpedition() {
    printf("+-----------------------------------------------------+\n");
    printf("|   Statistiky v expedici:                            |\n");
    printf("+-----------------------------------------------------+\n");
    printf("|   Average load time:            %fh\n", CarProcess::LoadTime/CarProcess::LoadAmount);
    printf("|   Average used cars:            %u\n", CarProcess::UsedCars);
    printf("|   Bottles(0.5l) for expedition: %u\n", Bottles_For_Expedition);
    printf("+-----------------------------------------------------+\n");
}
