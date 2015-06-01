#include "semaphores.h"
#include "common.h"
#include "waiting_room.h"
#include "agent_line.h"

extern struct waiting_room_struct waiting_room;
extern struct agent_line_struct agent_line;
extern struct shared_var num_customers_processed;

void initialize_semaphores()
{
	sem_init(&waiting_room.empty, 0, num_customers);
	sem_init(&waiting_room.full, 0, 0);
	sem_init(&waiting_room.mutex, 0, 1);
	
	sem_init(&all_customers_processed, 0, 0);
	sem_init(&(num_customers_processed.mutex), 0, 1);

	sem_init(&agent_line.empty, 0, 10);
	sem_init(&agent_line.full, 0, 0);
	sem_init(&agent_line.mutex, 0, 1);

}
