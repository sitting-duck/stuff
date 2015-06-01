#ifndef COMMON_H
#define COMMON_H

#include<list>
#include <semaphore.h>
#include "Debug.h"

using namespace std;

extern Debug dbg;

static const int num_agents = 4;

static const int num_customers = 100;

//note: this number has a mutex semaphore because it will be written to
//static int num_customers_processed = 0;

struct shared_var
{
	sem_t mutex;
	int value;
};

struct mutex {
	sem_t mut;

	void increment () {}
	void decrement () {};
	bool isLocked () {
	}
};

static struct shared_var num_customers_processed;

#endif

