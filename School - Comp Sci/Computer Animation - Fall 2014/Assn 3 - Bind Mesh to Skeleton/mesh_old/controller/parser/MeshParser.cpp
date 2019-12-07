#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "MeshParser.h"

typedef void (MeshParser::*TokenFunc) (std::string&);


MeshParser::TokenFunc MeshParser::StateFunction[] = {
	&MeshParser::gotBadToken,			//0
	&MeshParser::gotPositionsToken,		//1
	&MeshParser::gotNormalsToken,		//2
	&MeshParser::gotSkinWeightsToken,	//3
	&MeshParser::gotTrianglesToken,		//4
	&MeshParser::gotBindingsToken,		//5
};

MeshParser::MeshParser(){}

MeshParser::MeshParser(std::vector<std::string> _tokens, Skeleton* _skel)
{
	tokens = _tokens;
	skeleton = _skel;
	keywords["positions"] = positionsKeyword;
	keywords["normals"] = normalsKeyword;
	keywords["skinweights"] = skinWeightsKeyword;
	keywords["triangles"] = trianglesKeyword;
	keywords["bindings"] = bindingsKeyword;
	keywords["matrix"] = matrixKeyword;
}

MeshParser::~MeshParser(){}

void MeshParser::gotBadToken(std::string& _str)
{
	std::cout << "got bad token " << _str << std::endl;
}

void MeshParser::gotPositionsToken(std::string& _str)
{
	//std::cout << "got position keyword" << std::endl;
	//output << "got position keyword" << std::endl;

	std::string numVertsToken = getNextToken();

	//check if string is valid number
	if(!strIsNumber((char*)numVertsToken.c_str())){
		std::cout << "Error : MeshParser::gotPositionsToken :: invalid number token for num verts" << std::endl;
		//output << "invalid number token" << std::endl;
		exit(1);
	}
	int numVerts = atoi(numVertsToken.c_str());
	mesh.vertices.reserve(numVerts);
	openCurly();

	float x, y, z;
	for(int i = 0; i < numVerts; i++){
		//std::cout << "make vert" << std::endl;
		//output << "make vert" << std::endl;
		x = atof(getNextToken().c_str());
		y = atof(getNextToken().c_str());
		z = atof(getNextToken().c_str());
		//std::cout << "vert x= " << x << " y= " << y << " z= " << z << std::endl;
		//output << "vert x= " << x << " y= " << y << " z= " << z << std::endl;
		Vertex vert = Vertex();
		vert.position[0] = x;
		vert.position[1] = y;
		vert.position[2] = z;
		
		mesh.vertices.push_back(vert);
	}

	closeCurly();
}

void MeshParser::gotNormalsToken(std::string& _str)
{
	//std::cout << "got normals keyword" << std::endl;
	//output << "got normals keyword" << std::endl;

	std::string numNormalsToken = getNextToken();
	if(atoi(numNormalsToken.c_str()) != mesh.vertices.size()){
		std::cout << "ERROR: num normals must be equal to num positions. Num normals is " << numNormalsToken << " num positions is " << mesh.vertices.size() << std::endl;
		//output << "ERROR: num normals must be equal to num positions. Num normals is " << numNormalsToken << " num positions is " << mesh.vertices.size() << std::endl;
	}
	openCurly();
	float x, y, z;
	for(int i = 0; i < mesh.vertices.size(); i++){
		//std::cout << "make vert" << std::endl;
		//output << "make vert" << std::endl;
		x = atof(getNextToken().c_str());
		y = atof(getNextToken().c_str());
		z = atof(getNextToken().c_str());
		//std::cout << "vert x= " << x << " y= " << y << " z= " << z << std::endl;
		//output << "vert x= " << x << " y= " << y << " z= " << z << std::endl;
		mesh.vertices[i].normals[0] = x;
		mesh.vertices[i].normals[1] = y;
		mesh.vertices[i].normals[2] = z;
		mesh.vertices[i].normals[3] = 0;
	}
	closeCurly();

}

void MeshParser::gotSkinWeightsToken(std::string& _str)
{
	//std::cout << "got skin weights keyword" << std::endl;
	//output << "got skin weights keyword" << std::endl;

	std::string numSkinWeightsToken = getNextToken();
	if(atoi(numSkinWeightsToken.c_str()) != mesh.vertices.size()){
		std::cout << "ERROR: num skin weights must be equal to num positions. Num normals is " << numSkinWeightsToken << " num positions is " << mesh.vertices.size() << std::endl;
		//output << "ERROR: num skin weights must be equal to num positions. Num normals is " << numSkinWeightsToken << " num positions is " << model.vertices.size() << std::endl;
	}
	openCurly();

	std::string numAttachmentsToken;
	int numAttachments;
	int index;
	float weight;
	for(int i = 0; i < mesh.vertices.size(); i++){
		numAttachmentsToken = getNextToken();
		numAttachments = atoi(numAttachmentsToken.c_str());
		mesh.vertices[i].weights.reserve(numAttachments);
		//std::cout << "num attachments " << numAttachments << std::endl;
		//output << "num attachments " << numAttachments << std::endl;
		for(int j = 0; j < numAttachments; j++){
			index = atoi(getNextToken().c_str());
			//std::cout << "got index " << index << std::endl;
			//output << "got index " << index << std::endl;
			weight = atof(getNextToken().c_str());
			//std::cout << "got weight " << weight << std::endl;
			//output << "got weight " << weight << std::endl;
			
			JointWeight jointWeight = JointWeight(index, weight);
			mesh.vertices[i].weights.push_back(jointWeight);
		}
		checkSkinWeights(mesh.vertices[i].weights);
	}
	closeCurly();

}

bool MeshParser::checkSkinWeights(std::vector<JointWeight>& _weights){
	float weightSum = 0.0f;
	for(int j = 0; j < _weights.size(); j++){
		weightSum += _weights[j].weight;
	}

	if(weightSum != 1.0f){
		std::cout << "ERROR: MeshParser::checkSkinWeights : weights do not add to 1. weightSum = " << weightSum << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}

void MeshParser::gotTrianglesToken(std::string& _str)
{
	//std::cout << "got triangles keyword" << std::endl;
	std::string numTrianglesToken = getNextToken();
	int numTriangles = atoi(numTrianglesToken.c_str());
	openCurly();

	for(int i = 0; i < numTriangles; i++){
		Triangle tri;
		tri.vertIds[0] = atoi(getNextToken().c_str());
		tri.vertIds[1] = atoi(getNextToken().c_str());
		tri.vertIds[2] = atoi(getNextToken().c_str());
		mesh.triangles.push_back(tri);
	}
	closeCurly();
}

void MeshParser::gotBindingsToken(std::string& _str)
{
	//std::cout << "got bindings keyword" << std::endl;
	std::string numBindingsToken = getNextToken();
	int numBindings = atoi(numBindingsToken.c_str());

	//TODO:
	////if(numBindings != numJoints) ERRROOR!!!!!
	
	openCurly();

	std::string next;
	for(int i = 0; i < numBindings; i++){
		next = getNextToken();
		if(next == "matrix"){
			gotMatrixToken(i);
		}
		else{
			gotBadToken(next);
		}
	}
	closeCurly();
}

void MeshParser::gotMatrixToken(int _jointNumber)
{
	//std::cout << "got matrix keyword" << std::endl;

	float row0[4] = { 0, 0, 0, 0 };
	float row1[4] = { 0, 0, 0, 0 };
	float row2[4] = { 0, 0, 0, 0 };
	float row3[4] = { 0, 0, 0, 1 };
	Matrix4 matrix;

	openCurly();
	row0[0] = atof(getNextToken().c_str());
	row0[1] = atof(getNextToken().c_str());
	row0[2] = atof(getNextToken().c_str());

	row1[0] = atof(getNextToken().c_str());
	row1[1] = atof(getNextToken().c_str());
	row1[2] = atof(getNextToken().c_str());

	row2[0] = atof(getNextToken().c_str());
	row2[1] = atof(getNextToken().c_str());
	row2[2] = atof(getNextToken().c_str());

	row3[0] = atof(getNextToken().c_str());
	row3[1] = atof(getNextToken().c_str());
	row3[2] = atof(getNextToken().c_str());

	matrix.setRow(0, row0);
	matrix.setRow(1, row1);
	matrix.setRow(2, row2);
	matrix.setRow(3, row3);

	skeleton->operator[](_jointNumber).binding = matrix;

	closeCurly();
}

Mesh* MeshParser::getMesh()
{
	return &mesh;
}

void MeshParser::openCurly()
{
	std::string next = getNextToken(); //this token should always be an opening brace, any other token types are invalid in this state
	if(next != "{")
		gotBadToken(next);
}

void MeshParser::closeCurly()
{
	std::string next = getNextToken(); //this token should always be an opening brace, any other token types are invalid in this state
	if(next != "}")
		gotBadToken(next);
}

void MeshParser::parseTokens()
{
	std::string currentToken;
	MeshParser::TokenType currentTokenType;

	while(tokens.size() != 0){

		//get next token
		currentToken = getNextToken();

		//detrmine token type
		currentTokenType = getTokenType(currentToken);
		
		//void (MeshParser::*TokenFunc) (std::string&) = StateFunction[currentTokenType];
		//(this->*TokenFunc)(currentToken);

		switch(currentTokenType){
		case positionsKeyword:
			gotPositionsToken(currentToken);
			break;
		case normalsKeyword:
			gotNormalsToken(currentToken);
			break;
		case skinWeightsKeyword:
			gotSkinWeightsToken(currentToken);
			break;
		case trianglesKeyword:
			gotTrianglesToken(currentToken);
			break;
		case bindingsKeyword:
			gotBindingsToken(currentToken);
			break;
		default:
			gotBadToken(currentToken);
			break;
		}
	}
}

MeshParser::TokenType MeshParser::getTokenType(std::string& _str)
{
	it = keywords.find(_str);

	if(it != keywords.end()){ //token is a keyword
		return it->second;	//return token type
	}
	else{
		return badToken;
	}
}

std::string MeshParser::getNextToken()
{
	std::string token = tokens.front();
	tokens.erase(tokens.begin());
	return token;
}
