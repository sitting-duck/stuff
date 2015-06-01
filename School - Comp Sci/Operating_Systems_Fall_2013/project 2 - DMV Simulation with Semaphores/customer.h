#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <pthread.h>

void create_customer_threads();
void join_customer_threads();
void* customer_controller(void* _arg);

struct customer_struct
{
	unsigned int customer_number;

	sem_t mutex_customer_number;

	unsigned int ticket_number;

	sem_t mutex_ticket_number;

	pthread_t thread_number;

	sem_t processed;

	customer_struct();
	customer_struct(const customer_struct& rhs);
	customer_struct& operator=(const customer_struct& rhs);
};

#endif
