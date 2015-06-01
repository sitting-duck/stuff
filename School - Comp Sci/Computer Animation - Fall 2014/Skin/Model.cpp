#include "Model.h"

Model::Model(tree<BallJoint> _skelTree, int _numJoints){
	numJoints = _numJoints;
	std::cout << "in model: numJoints is " << numJoints << std::endl;
	skelTree = _skelTree;
}

/*
Model::Model(const Model& _model){
	vertices = _model.vertices;
	triangles = _model.triangles;
	bindings = _model.bindings;
	transforms = _model.transforms;
	skelTree = _model.skelTree;
}*/

Model::~Model(){}

/**
Model& Model::operator=(const Model& _model){
	vertices = _model.vertices;
	triangles = _model.triangles;
	bindings = _model.bindings;
	transforms = _model.transforms;
	skelTree = _model.skelTree;
	return *this;
}*/

/*
bool Model::operator ==(const Model& _model) const{
	if(vertices == _model.vertices){
		return true;
	}
	else{
		return false;
	}
}*/

void Model::printVerts(){
	for(int i = 0; i < vertices.size(); i++){
		std::cout << "vert " << i << std::endl;
		std::cout << "position: " << std::endl;
		std::cout << "\t" << vertices[i].pos[0] << std::endl; 
		std::cout << "\t" << vertices[i].pos[1] << std::endl;
		std::cout << "\t" << vertices[i].pos[2] << std::endl;
		std::cout << "normals: " << std::endl;
		std::cout << "\t" << vertices[i].normals[0] << std::endl;
		std::cout << "\t" << vertices[i].normals[1] << std::endl;
		std::cout << "\t" << vertices[i].normals[2] << std::endl;
		std::cout << "weights: " << std::endl;
		for(int j = 0; j < vertices[i].weights.size(); j++){
			std::cout << "\t" << vertices[i].weights[j].index << " ";
			std::cout << vertices[i].weights[j].weight << std::endl;
		}
	}
}

/*void Model::printBindings(){
	std::cout << "bindings:" << std::endl;
	for(int i = 0; i < numJoints; i++){
		std::cout << bindings[i] << std::endl;
	}
}*/

void Model::generateTransforms(){
	std::cout << "gen transforms" << std::endl;
	//printTree();
	tree<BallJoint>::iterator it;
	for(int i = 0; i < numJoints; i++){
		it = getJointByIndex(i);
		//std::cout << "got joint " << it->name << std::endl;
		Matrix4 transform = (it->world)*(it->binding.invert());
		//Matrix4 transform = (it->binding.invert())*(it->world);
		//transforms.push_back(transform);
		it->transform = transform;

		it++;
	}
	printTransforms();
}

void Model::weightVertices(){
	tree<BallJoint>::iterator it;

	for(int i = 0; i < vertices.size(); i++){
		Vertex initVert = vertices[i];
		
		Vector4 initVectVert;
		initVectVert[0] = initVert.pos[0];
		initVectVert[1] = initVert.pos[1];
		initVectVert[2] = initVert.pos[2];
		initVectVert[3] = 1.0f;

		Vector4 weightedVertVect;

		for(int j = 0; j < initVert.weights.size(); j++){
			
			//get the transform matrix from the joint
			//tree<BallJoint>::iterator it = getJointByIndex(initVert.weights[j].index);
			//Matrix4 transform = transforms[initVert.weights[j].index];
			int currentJointIndex = initVert.weights[j].index;
			it = getJointByIndex(currentJointIndex);
			//std::cout << "in weightverts: got joint " << it->name << std::endl;
			Matrix4 transform = it->transform;
			//float weight = initVert.weights[j].weight;
			float weight = initVert.weights[j].weight;

			//weightedVertVect = weightedVertVect + (weight * transform * initVectVert);
			weightedVertVect = weightedVertVect + (weight * initVectVert * transform);
		}

		Vertex weightedVert;
		weightedVert.pos[0] = weightedVertVect[0];
		weightedVert.pos[1] = weightedVertVect[1];
		weightedVert.pos[2] = weightedVertVect[2];

		vertices[i] = weightedVert;

		//reset weightVertVect
		weightedVertVect[0] = 0; weightedVertVect[1] = 0; weightedVertVect[2] = 0; weightedVertVect[3] = 0;
	}
}

void Model::printTransforms(){
	tree<BallJoint>::pre_order_iterator it;
	it = skelTree.begin();
	while(it != skelTree.end()){
		std::cout << it->name << std::endl;
		std::cout << it->transform << std::endl;
		it++;
	}
}

void Model::printTriangles(){
	//out << "triangles: " << std::endl;
	for(int i = 0; i < triangles.size(); i++){
		std::cout << triangles[i].verts[0] << " " << triangles[i].verts[1] << " " << triangles[i].verts[2] << std::endl;
		//out << triangles[i].verts[0] << " " << triangles[i].verts[1] << " " << triangles[i].verts[2] << std::endl;
	}
}

void Model::drawTriangles(){
	//std::cout << "draw triangles: " << std::endl;
	float x0, y0, z0, x1, y1, z1, x2, y2, z2;

	for(int i = 0; i < triangles.size(); i++){
		x0 = vertices[triangles[i].verts[0]].pos[0];
		y0 = vertices[triangles[i].verts[0]].pos[1];
		z0 = vertices[triangles[i].verts[0]].pos[2];

		x1 = vertices[triangles[i].verts[1]].pos[0];
		y1 = vertices[triangles[i].verts[1]].pos[1];
		z1 = vertices[triangles[i].verts[1]].pos[2];

		x2 = vertices[triangles[i].verts[2]].pos[0];
		y2 = vertices[triangles[i].verts[2]].pos[1];
		z2 = vertices[triangles[i].verts[2]].pos[2];
	
		glMatrixMode(GL_MODELVIEW);
		
		glBegin(GL_LINES);

		//vert 0 to vert 1
		glVertex3f(x0, y0, z0);
		glVertex3f(x1, y1, z1);

		//vert 1 to vert 2
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y2, z2);

		//vert 2 to vert 0
		glVertex3f(x2, y2, z2);
		glVertex3f(x0, y0, z0);

		glEnd();
	}
}

tree<BallJoint>::iterator& Model::getJointByIndex(int _index){
	tree<BallJoint>::pre_order_iterator it;
	it = skelTree.begin();
	while(it != skelTree.end()){
		//std::cout << "at joint " << it->name << " index " << it->index << std::endl;
		if(it->index == _index){
			return it;
		}
		it++;
	}
	std::cout << "error: no joint with index " << _index << " in tree" << std::endl;
	it--;
	return it;
}

void Model::printTree(){
	tree<BallJoint>::iterator it, end;
	tree<BallJoint>::sibling_iterator sib;
	tree<BallJoint>::fixed_depth_iterator fdi, fdi_end;

	it = skelTree.begin();
	//std::cout << "begin: " << it->getName() << std::endl;
	end = skelTree.end();
	//std::cout << "end: " << end->getName() << std::endl;
	int maxDepth = skelTree.max_depth();
	//std::cout << "max depth: " << maxDepth << std::endl;

	for(int i = 0; i < skelTree.max_depth() + 1; i++){
		fdi = skelTree.begin_fixed(skelTree.begin(), i);
		//fdi_end = tr.end_fixed(tr.begin(), i);

		//print dat level tho
		while(skelTree.is_valid(fdi)){
			std::cout << fdi->getName() << " ";
			fdi++;
		}
		std::cout << std::endl;
	}
}