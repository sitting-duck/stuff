#ifndef AGENT_H
#define AGENT_H

#include <semaphore.h>

void create_agent_threads();

void join_agent_threads();

void signal_handler(int signum);

void* agent_controller(void* _arg);

struct agent_struct
{
	sem_t mutex;
};



#endif
