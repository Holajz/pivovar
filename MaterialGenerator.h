//
// Created by thomas on 23.11.17.
//

#ifndef IMS_PROJ_SKLADMATERIALU_H
#define IMS_PROJ_SKLADMATERIALU_H

#include <simlib.h>
#include <iostream>


class MaterialStore
{
    class MaterialGenerator : public Process
    {

    private:
        double g_generateMaterialTime;
        unsigned int g_generatedAmount;
        Store* g_store;
        unsigned int initializedAmount;

    public:

        MaterialGenerator(unsigned int generatedAmount, double generateTime, Store *store, unsigned int initializedAmount);

        void Behavior();

    };


private:

    Store* store;
    MaterialGenerator *generator;
    int usedAmount;

public:

    MaterialStore(const char* storeName, unsigned int capacity, unsigned int initializedAmount,
                   double generatedTime, unsigned int generatedAmount);

    ~MaterialStore();

    bool isFull();

    void get(Entity *entity, unsigned int amount);

    void put(unsigned long amount);

    void activate();

    void output();


};


#endif //IMS_PROJ_SKLADMATERIALU_H
