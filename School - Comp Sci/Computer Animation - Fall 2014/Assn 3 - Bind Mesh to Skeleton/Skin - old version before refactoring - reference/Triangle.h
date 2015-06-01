#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glui.h>
#include "Vertex.h"

class Triangle{

public:
	Triangle();
	Triangle(const Triangle& _tri);
	~Triangle();
	bool operator==(const Triangle& _tri) const;
	Triangle& operator=(const Triangle& _tri);

	int verts[3];
};

#endif