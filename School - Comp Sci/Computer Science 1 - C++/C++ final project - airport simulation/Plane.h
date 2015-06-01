#ifndef PLANE_H
#define PLANE_H

#include "PartyList.h"

struct Plane
	{
	bool					Initialized;
	unsigned int			NumSeats;
	unsigned int			AvailSeats;
	unsigned int			NumParties;
	PartyList*				myPartyList;
	char					PlaneId;
	char					PlaneName[6];
	};

#endif
