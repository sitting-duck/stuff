#include <pthread.h>
#include "threads.h"
#include "waiting_room.h"
#include "info_desk.h"
#include "semaphores.h"
#include "customer.h"

extern customer_struct current_customer;
extern struct waiting_room_struct waiting_room;

//the info desk object
info_desk_line_struct info_desk_line;

void create_info_desk_thread()
{
	if(pthread_create(&info_desk_thread, NULL, info_desk_controller, NULL))
	{
		dbg.log("[r]error creating info desk thread[/]\n");
		exit(1);
	}
	dbg.log("[g]info desk created[/]\n");
}

void join_info_desk_thread()
{
	if(pthread_join(info_desk_thread, NULL))
	{
		dbg.log("[r]error joining info desk thread[/]\n");
		exit(1);
	}
	dbg.log("[m]info desk was joined[/]\n");
}

void* info_desk_controller(void* _arg)
{

	sem_init(&info_desk_line.full, 0, 0);
	sem_init(&info_desk_line.empty, 0, 10);
	sem_init(&info_desk_line.mutex, 0, 1);

	unsigned int current_ticket_number = 1;
	struct customer_struct current_customer;

	for(int num_customers_ticketed = 0; num_customers_ticketed < num_customers; num_customers_ticketed++)
	{
		//wait until there is someone in line
		sem_wait(&info_desk_line.full);
		
		//make sure noone is touching the line
		sem_wait(&info_desk_line.mutex);
		
		//assign the customer a number
		current_customer = info_desk_line.line.front();
		current_customer.ticket_number = current_ticket_number++;
		dbg.log("[c]customer %i gets number %i, waits to be called[/]\n", current_customer.customer_number, current_customer.ticket_number);

		//customer gets out of info desk line
		info_desk_line.line.pop_front();

		//indicate that there is an empty spot in the line now
		sem_post(&info_desk_line.empty); 

		//release the waiting line
		sem_post(&info_desk_line.mutex);

		//make sure noone is touching the waiting room
		sem_wait(&waiting_room.mutex);

		//make sure there is room in the waiting room
		//note: the waiting room always has enough room
		//because we initialized it to size of num_customers, 
		//but the semaphores are here for book keeping 
		//purposes
		sem_wait(&waiting_room.empty);

		//put the customer at the end of the waiting line 
		//queue. Note: although in a waiting room, people
		//don't sit in order, they will be leaving in order
		//so we will use a std::list
		waiting_room.line.push_back(current_customer);

		//let everyone know there is one more in the waiting room
		sem_post(&waiting_room.full);

		//release the waiting_room for other threads to touch
		sem_post(&waiting_room.mutex);
		
	}

	return NULL;
}
