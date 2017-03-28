#ifndef WAITING_ROOM_H
#define WAITING_ROOM_H

#include <list>
#include <semaphore.h>

using namespace std;

struct waiting_room_struct
{
	sem_t empty;
	sem_t full;
	sem_t mutex;

	list<struct customer_struct> line;
};

#endif
