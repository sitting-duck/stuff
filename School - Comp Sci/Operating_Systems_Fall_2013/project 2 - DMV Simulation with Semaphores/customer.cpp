#include "common.h"
#include "info_desk.h"
#include "customer.h"
#include "threads.h"
#include "semaphores.h"
#include "Debug.h"

extern struct info_desk_line_struct info_desk_line;

void create_customer_threads()
{
	for(int i = 0; i < num_customers; i++)
	{
		if(pthread_create(&cust_thread_id[i], NULL, customer_controller, (void*)i))
		{
				dbg.log("[r]Error creating customer thread # [/]\n");
				exit(1);
		}
		dbg.log("[g]customer %i created[/]\n", i);
	}
}

void join_customer_threads()
{
	for(int	i = 0; i < num_customers; i++)
	{
		if(pthread_join(cust_thread_id[i], NULL))
		{
			cout << "Error joining customer thread # " << i << endl;
			exit(1);
		}
		dbg.log("[m]customer %i was joined[/]\n", i);
	}
}

void* customer_controller(void* _arg)
{

	int customer_number = *((int*)&_arg);

	customer_struct customer;
	sem_init(&customer.mutex_customer_number, 0, 1);
	sem_init(&customer.mutex_ticket_number, 0, 1);
	sem_init(&customer.processed, 0, 0);
	sem_post(&customer.processed);

	//make sure nothing else is touching customer number
	sem_wait(&customer.mutex_customer_number);

	//assign the number
	customer.customer_number = customer_number;
	
	//release the number for other threads to touch
	sem_post(&customer.mutex_customer_number);

	//check if there is room in info desk line
	sem_wait(&(info_desk_line.empty));

	//check if any other thread is touching the line
	sem_wait(&(info_desk_line.mutex));

	//get in the back of the line.
	info_desk_line.line.push_back(customer);
	dbg.log("[c]customer %i enters DMV[/]\n", customer_number); 

	//let the info desk know someone is in line now
	sem_post(&(info_desk_line.full));

	//release access to the line for other threads to touch
	sem_post(&(info_desk_line.mutex));
	
	//wait until this customer has been processed to exit
	sem_wait(&customer.processed);

	return NULL;	
}

customer_struct::customer_struct()
{

}

customer_struct::customer_struct(const customer_struct& rhs)
{
	customer_number = rhs.customer_number;
	mutex_customer_number = rhs.mutex_customer_number;
	ticket_number = rhs.ticket_number;
	thread_number = rhs.thread_number;
}

customer_struct& customer_struct::operator=(const customer_struct& rhs)
{
	customer_number = rhs.customer_number;
	mutex_customer_number = rhs.mutex_customer_number;
	ticket_number = rhs.ticket_number;
	thread_number = rhs.thread_number;
	return *this;
}
