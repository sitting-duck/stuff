#include <pthread.h>
#include "common.h"
#include "Debug.h"
#include "waiting_room.h"
#include "semaphores.h"
#include "threads.h"
#include "agent.h"
#include "announcer.h"
#include "customer.h"
#include "agent_line.h"

extern struct announcer_struct announcer;
extern struct shared_var num_customers_processed;
extern struct agent_line_struct agent_line;

void create_agent_threads()
{
	for(int i = 0; i < num_agents; i++)
	{
		if(pthread_create(&agent_thread_id[i], NULL, agent_controller, (void*) i))
		{
			dbg.log("[r]error creating agent thread # %d[/]\n", i);
			exit(1);
		}
		dbg.log("[g]agent %i created[/]\n", i);
	}
}

void join_agent_threads()
{
	for(int i = 0; i < num_agents; i++)
	{
		if(pthread_join(agent_thread_id[i], NULL))
		{
			dbg.log("[r]error joining agent thread # %d[/]\n", i);
			exit(1);
		}
		dbg.log("[m]agent %i was joined[/]\n", i);
	}
}

void signal_handler(int signum)
{
	pthread_exit(NULL);
}

void* agent_controller(void* _arg)
{
	int agent_number = *((int*)&_arg);
	struct agent_struct agent;
	struct customer_struct current_customer;

	sem_init(&agent.mutex, 0, 1);

	//while(num_customers_processed.value != num_customers)
	while(true)
	{

		//if this thread processed the last customer, kill all the other agent threads
		if(num_customers_processed.value == num_customers)
		{
			//kill all the other threads
			for(int thread = 0; thread < num_agents; thread++)
			{
				if(thread != agent_number)
				{
					pthread_cancel(agent_thread_id[thread]);
				}
			}
			break;
		}

		//wait until there 1 or more person in waiting line
		sem_wait(&agent_line.full);
		
		//let everyone know this agent is occupied with a customer
		sem_wait(&agent.mutex);

		//make sure nothing else is touching the agent line
		sem_wait(&agent_line.mutex);

		//first customer gets out line and comes to agent station
		current_customer = agent_line.line.front();
		agent_line.line.pop_front();

		//tell everyone there is one less person in the line
		sem_post(&agent_line.empty);

		//release the line so other threads can touch it
		sem_post(&agent_line.mutex);

		//process the customer	
		dbg.log("[r]agent %i serving customer %i[/]\n", agent_number, current_customer.customer_number);

		dbg.log("[r]agent %i asks customer %i to take photo and eye exam[/]\n", agent_number, current_customer.customer_number);

		dbg.log("[r]customer %i completes photo and eye exam for agent %i[/]\n", agent_number, current_customer.customer_number);

		dbg.log("[r]agent %i gives license to customer %i[/]\n", agent_number, current_customer.customer_number);

		dbg.log("[r]customer %i gets license and departs[/]\n", current_customer.customer_number);
		
		//make sure nothing else is touching num processed
		sem_post(&(num_customers_processed.mutex));
		sem_wait(&(num_customers_processed.mutex));

		num_customers_processed.value++;
		//cout << "agent: " << agent_number << " ncP: " << num_customers_processed.value << endl
		
		//release num processed
		sem_post(&(num_customers_processed.mutex));	

		//let customer thread know it can exit now
		sem_post(&current_customer.processed);

		//let everyone know this agent is free
		sem_post(&agent.mutex);
	}

	return NULL;	
}

