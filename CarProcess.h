//
// Created by thomas on 24.11.17.
//

#ifndef IMS_PROJ_CAR_PROCESS_H
#define IMS_PROJ_CAR_PROCESS_H

#include <simlib.h>
#include "main.h"

class CarProcess : public Process
{
	private:
		const double MIN_TRANSPORT_TIME = 12;
		const double MAX_TRANSPORT_TIME = 24;
		const unsigned int CAR_CAPACITY = 12;
		const unsigned int LOAD_AMOUNT = 2000;
		const double LOADING_TIME = 5 MINUTE;

	public:
		static unsigned int LoadAmount;
		static double LoadTime;
		static unsigned int UsedCars;

		void Behavior();

		static void PrintInfoAboutExpedition();
};


#endif