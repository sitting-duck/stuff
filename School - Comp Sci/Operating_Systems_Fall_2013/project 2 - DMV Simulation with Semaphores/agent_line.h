#ifndef AGENT_LINE_H
#define AGENT_LINE_H

#include <list>
#include <semaphore.h>

using namespace std;

struct agent_line_struct
{
	sem_t empty;
	sem_t full;
	sem_t mutex;

	list<struct customer_struct> line;
};

#endif
