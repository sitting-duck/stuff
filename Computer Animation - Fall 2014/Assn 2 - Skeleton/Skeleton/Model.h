#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Vertex.h"

class Model{

public:

	Model();
	Model(const Model&);
	~Model();

	Model& operator=(Model _model);
	bool operator ==(const Model& _model) const;

private:
	std::vector<Vertex> vertices;
	//vector<Triangle> triangles;
};

#endif