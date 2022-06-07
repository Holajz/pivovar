//
// Created by thomas on 23.11.17.
//

#include "MaterialGenerator.h"
using namespace std;

MaterialStore::MaterialGenerator::MaterialGenerator(unsigned int generatedAmount, double generateTime, Store *store, unsigned int initmount)
{
    g_generatedAmount = generatedAmount;
    g_generateMaterialTime = generateTime;
    g_store = store;
    initializedAmount = initmount;
}

void MaterialStore::MaterialGenerator::Behavior()
{

    g_store->Enter(this, g_store->Capacity()-initializedAmount);

    while(1) {

        //if after generating material store has no capacity for all material
        if (g_store->Used() <= g_generatedAmount)
        {
            g_store->Leave(g_store->Used());
            WaitUntil(g_store->Used() > g_generatedAmount);
        }
        //after generating material store has capacity for all material
        else {
            g_store->Leave(g_generatedAmount);
        }

        Wait(g_generateMaterialTime);
    }
}

MaterialStore::MaterialStore(const char *storeName, unsigned const int capacity, unsigned const int initializedAmount,
                               double generatedTime, unsigned int generatedAmount)
{
    store = new Store(storeName, capacity);

    if(capacity >= initializedAmount) {
        generator = new MaterialGenerator(generatedAmount, generatedTime, store, initializedAmount);
    }
    else {
        generator = new MaterialGenerator(generatedAmount, generatedTime, store, 0);
    }

}

MaterialStore::~MaterialStore() 
{
    delete store;

    if(generator == nullptr) {
        return;
    }
    generator->Cancel();
}

bool MaterialStore::isFull()
{
    return store->Full();
}

void MaterialStore::get(Entity *entity, unsigned int amount)
{
    store->Enter(entity, amount);
    usedAmount = usedAmount + amount;
}

void MaterialStore::activate()
{
    if(generator == nullptr) {
        return;
    }

    generator->Activate();
}

void MaterialStore::output()
{
    printf("|  Pouzity material: %d\n", usedAmount);
    store->Output();
}



