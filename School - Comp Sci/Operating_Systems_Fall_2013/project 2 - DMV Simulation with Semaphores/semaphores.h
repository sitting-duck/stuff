#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <semaphore.h>
#include <list>

void initialize_semaphores();

static sem_t mutex_num_customers_processed;

static sem_t all_customers_processed; 

#endif
