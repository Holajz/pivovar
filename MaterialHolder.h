//
// Created by thomas on 24.11.17.
//

#ifndef IMS_PROJ_MATERIALHOLDER_H
#define IMS_PROJ_MATERIALHOLDER_H

#include <simlib.h>
#include <stdio.h>


class MaterialHolder {
private:

    unsigned int materialAmount;
    unsigned int usedAmount;
    unsigned int materialType;
    unsigned int capacity;
    unsigned int capWasSet;
    unsigned int max_amount;
    unsigned int min_amount;

public:
    
    MaterialHolder(unsigned int capacity,
                   unsigned int initializedAmount, unsigned int material_type);

    void get(unsigned int amount);

    void put(unsigned int amount);

    bool isMaxCapacity();

    unsigned int Capacity();

    bool hasMaterial(unsigned int needed_material);

    unsigned int MinAmount();

    unsigned int Amount();

    void Sell(unsigned int amount);

    int type();

    void output();
};


#endif //IMS_PROJ_MATERIALHOLDER_H
