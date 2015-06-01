#ifndef ANNOUNCER_H
#define ANNOUNCER_H

#include <list>
#include <semaphore.h>



void create_announcer_thread();	
void join_announcer_thread();	
void* announcer_controller(void* _arg);

struct announcer_struct
{

};

#endif
