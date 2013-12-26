#include <pthread.h>
#include "common.h"
#include "announcer.h"
#include "waiting_room.h"
#include "customer.h"
#include "threads.h"
#include "semaphores.h"
#include "agent_line.h"

struct announcer_struct announcer;
extern struct waiting_room_struct waiting_room;
extern struct agent_line_struct agent_line;

void create_announcer_thread()
{
	if(pthread_create(&announcer_thread, NULL, announcer_controller, NULL))
	{
		dbg.log("[r]error creating announcer thread[/]\n");
		exit(1);
	}
	dbg.log("[g]announcer created[/]\n");
}

void join_announcer_thread()
{
	if(pthread_join(announcer_thread, NULL))
	{
		dbg.log("[r]error joining announcer thread[/]\n");
		exit(1);
	}
	dbg.log("[m]announcer was joined[/]\n");
}

void* announcer_controller(void* _arg)
{
	int current_ticket_number = 1;
	struct customer_struct current_customer;
	

	for(int current_ticket_number = 1; current_ticket_number <= num_customers; current_ticket_number++)
	{
		//make sure there is room in the agent waiting line
		sem_wait(&agent_line.empty);

		//wait until there is 1 person or more in the waiting room
		sem_wait(&waiting_room.full);

		//call the current ticket number
		dbg.log("[y]announcer calls number %i[/]\n", current_ticket_number);

		//make sure nothing is touching the waiting room
		sem_wait(&waiting_room.mutex);

		//customer leaves waiting room
		//this cusotmer will have the matching number
		//because customers are called in the order they
		//are given ticket numbers
		current_customer = waiting_room.line.front();
		waiting_room.line.pop_front();

		//release the waiting room for other threads to touch
		sem_post(&waiting_room.mutex);

		//make sure nothing is touching the agent waiting line
		sem_wait(&agent_line.mutex);

		//customer gets in line to see an agent
		agent_line.line.push_back(current_customer);

		//let everyone know there is one more person in the agent waiting line
		sem_post(&agent_line.full);

		//release the agent waiting line for other processes to touch
		sem_post(&agent_line.mutex);
	}

	return NULL;
}
