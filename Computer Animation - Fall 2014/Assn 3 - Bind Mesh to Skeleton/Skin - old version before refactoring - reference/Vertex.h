#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include "Vectors.h"

class Vertex{

public:

	class JointWeight{
	public:
		int index;
		float weight;

		JointWeight(int _index, float _weight): index(_index), weight(_weight){}
		~JointWeight(){}
		bool operator==(const JointWeight& _jw) const {
			if((index != _jw.index) || (weight != _jw.weight)){
				return false;
			}
			else{ return true; }
		}
	};

	Vertex();
	Vertex(const Vertex& _vert);
	~Vertex();

	Vertex& operator=(Vertex _vect);
	bool operator==(const Vertex& _vert) const;

	const static int DOF = 3;
	Vector4 pos;
	Vector4 normals;
	std::vector<JointWeight> weights;
};

#endif