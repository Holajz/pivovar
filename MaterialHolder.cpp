//
// Created by thomas on 24.11.17.
//

#include "MaterialHolder.h"
using namespace std;

MaterialHolder::MaterialHolder(unsigned const int cap, unsigned const int initializedAmount, unsigned const int material_type)
{
    materialAmount = initializedAmount;
    materialType = material_type;
    capacity = cap;

    max_amount = initializedAmount;
    min_amount = initializedAmount;
    usedAmount = 0;
    capWasSet = 0;
}

void MaterialHolder::get(unsigned int amount)
{
    materialAmount -= amount;
    usedAmount += amount;

    if(min_amount > materialAmount) {
        min_amount = materialAmount;
    }
}

void MaterialHolder::put(unsigned int amount)
{
    if(materialAmount+amount >= capacity) {
        materialAmount = capacity;
        capWasSet++;
    }

    materialAmount += amount;



    if(max_amount < materialAmount) {
        max_amount = materialAmount;
    }
}

bool MaterialHolder::isMaxCapacity()
{
    return materialAmount >= capacity;
}

unsigned int MaterialHolder::Capacity()
{
    return capacity;
}

bool MaterialHolder::hasMaterial(unsigned int needed_material)
{
    if(materialAmount < needed_material) {
        return false;
    }
    return true;
}

int MaterialHolder::type()
{
    return materialType;
}

void MaterialHolder::output()
{
    printf("+-----------------------------------------------------+\n");
    printf("|   Pouzity material:        %d\n", usedAmount);
    printf("|   Maximální množství:      %d\n", max_amount);
    printf("|   Minimální množství:      %d\n", min_amount);
    printf("|   Materiálu ve skladu      %d\n", materialAmount);
    printf("|   Počet dovršení kapacity: %d\n", capWasSet);
    printf("+-----------------------------------------------------+\n");
}

unsigned int MaterialHolder::MinAmount() {
    return min_amount;
}

unsigned int MaterialHolder::Amount() {
    return materialAmount;
}

void MaterialHolder::Sell(unsigned int amount) {
    materialAmount -= amount;
}
