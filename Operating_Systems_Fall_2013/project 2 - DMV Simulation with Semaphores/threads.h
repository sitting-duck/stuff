#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include "common.h"

static pthread_t cust_thread_id[num_customers];

static pthread_t agent_thread_id[num_agents];

static pthread_t info_desk_thread;

static pthread_t announcer_thread;

#endif
