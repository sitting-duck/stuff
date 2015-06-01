#ifndef MESH_PARSER_H
#define MESH_PARSER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <assert.h>

#include "Model.h"
#include "Mesh.h"
#include "StrIsNum.h"
#include "JointWeight.h"

class MeshFactory;

class MeshParser
{
	friend Mesh;
	friend Triangle;
	friend Vertex;
	friend JointWeight;
	friend Model;
	friend MeshFactory;

private:
	Mesh mesh;
	Skeleton* skeleton;

	enum TokenType{
		badToken,
		positionsKeyword,
		normalsKeyword,
		skinWeightsKeyword,
		trianglesKeyword,
		bindingsKeyword,
		matrixKeyword,
		numTokenTypes
	};

	typedef void (MeshParser::*TokenFunc)(std::string&);

	std::vector<std::string> tokens;

	std::map<std::string, MeshParser::TokenType> keywords;

	std::map<std::string, MeshParser::TokenType>::iterator it;

	static TokenFunc StateFunction[];

public:
	MeshParser();

	MeshParser(std::vector<std::string> _tokens, Skeleton* _skel);

	~MeshParser();

	void gotBadToken(std::string& _str);

	void gotPositionsToken(std::string& _str);

	void gotNormalsToken(std::string& _str);

	void gotSkinWeightsToken(std::string& _str);

	bool checkSkinWeights(std::vector<JointWeight>& _weights);

	void gotTrianglesToken(std::string& _str);

	void gotBindingsToken(std::string& _str);

	void gotMatrixToken(int _jointNumber);

	Mesh* getMesh();

	void openCurly();

	void closeCurly();

	void parseTokens();

	TokenType getTokenType(std::string& _str);

	std::string getNextToken();

};
#endif
