#ifndef INFO_DESK_H
#define INFO_DESK_H

#include <list>

using namespace std;

void create_info_desk_thread();

void join_info_desk_thread();

void* info_desk_controller(void* _arg);

struct info_desk_line_struct
{	
	sem_t full;  //keeps track of the number of full spots
	sem_t empty; //keeps track of the number of empty spots
	sem_t mutex;

	list<struct customer_struct> line;			
};



#endif
