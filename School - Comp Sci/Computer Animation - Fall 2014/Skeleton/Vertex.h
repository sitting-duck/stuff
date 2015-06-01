#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vertex{

public:
	Vertex();
	Vertex(Vertex& _vert);
	~Vertex();

	Vertex& operator=(Vertex _vect);
	bool operator==(const Vertex& _vert) const;

private:
	const static int DOF = 3;
	float pos[DOF];
	float normals[DOF];
	std::vector<float> weights;
};

#endif