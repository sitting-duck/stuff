#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "Debug.h"
Debug dbg;
#include "common.h"
#include "waiting_room.h"
#include "semaphores.h"
#include "threads.h"
#include "info_desk.h"
#include "announcer.h"
#include "agent.h"
#include "customer.h"

using namespace std;

int main()
{

	initialize_semaphores();

	create_info_desk_thread();
	create_announcer_thread();	
	create_agent_threads();
	create_customer_threads();

	join_customer_threads();
	join_agent_threads();
	join_announcer_thread();	
	join_info_desk_thread();
	
	return 0;

}



