
#include <iostream>
#include <regex>
#include "SkinParser.h"

typedef unsigned int uint;

SkinParser::TokenFunc SkinParser::StateFunction[] = {
	&SkinParser::gotBadToken,				//0
	&SkinParser::gotPositionsKeyword,		//1
	&SkinParser::gotNormalsKeyword,			//2
	&SkinParser::gotSkinWeightsKeyword,		//3
	&SkinParser::gotTrianglesKeyword,		//4
	&SkinParser::gotBindingsKeyword,		//5
	&SkinParser::gotNumToken,				//7
	&SkinParser::gotOpenCurlyToken,			//8
	&SkinParser::gotCloseCurlyToken			//9
};

SkinParser::uchar SkinParser::StateTable[SkinParser::numTokenTypes][SkinParser::numStates] = {
	//						start   afterPositions   afterNormals   afterSkinWeights   afterTriangles   afterBindings   
	/*badToken,*/			{ 0,          0,				0,				0,				0,				0,			},
	/*positionsKeyword,*/	{ 1,          0,				0,				0,				0,				0,			},
	/*normalsKeyword,*/		{ 0,          2,				0,				0,				0,				0,			},
	/*skinWeightsKeyword,*/	{ 0,          0,				3,				0,				0,				0,			},
	/*trianglesKeyword,*/	{ 0,          0,				0,				4,				0,				0,			},
	/*bindingsKeyword,*/	{ 0,          0,				0,				0,				5,				0,			},
	/*matrixKeyword,*/		{ 0,          0,				0,				0,				0,				0,			},
	/*numToken,*/			{ 0,          0,				0,				0,				0,				0,			},
	/*openCurlyToken,*/		{ 0,          0,				0,				0,				0,				0,			},
	/*closeCurlyToken,*/	{ 0,          0,				0,				0,				0,				0,			}
}; 


SkinParser::SkinParser(){
	//output.open("output.txt");
}

SkinParser::SkinParser(const SkinParser& _sp){}

SkinParser& SkinParser::operator =(SkinParser _sp){
	skelTree = _sp.skelTree;
	model = _sp.model;
	strList = _sp.strList;
	tokenList = _sp.tokenList;
	keywordMap = _sp.keywordMap;
	return *this;
}

SkinParser::SkinParser(const std::vector<std::string>& _tokenList, tree<BallJoint>& _tree, int _numJoints) : strList(_tokenList){
	
	numJoints = _numJoints;
	skelTree = _tree;
	model = Model(_tree, numJoints);
	output.open("output.txt", std::ofstream::out);
	
	for(uint i = 0; i < strList.size(); i++){
		auto token = Token(strList[i]);
		tokenList.push_back(token);
	}
	
	keywordMap["positions"] = positionsKeyword;
	keywordMap["normals"] = normalsKeyword;
	keywordMap["skinweights"] = skinWeightsKeyword;
	keywordMap["triangles"] = trianglesKeyword;
	keywordMap["bindings"] = bindingsKeyword;
	keywordMap["matrix"] = matrixKeyword;

	parseTokens(tokenList);
	model.generateTransforms();
	model.weightVertices();
}

SkinParser::~SkinParser(){
	output.close();
}

SkinParser::Token SkinParser::getNextToken(){
	if(tokenList.size() == 0){
		Token token = Token();
		return token;
	}
	else{
		Token token = tokenList.front();
		tokenList.erase(tokenList.begin());
		return token;
	}
}

SkinParser::TokenType SkinParser::getTokenType(SkinParser::Token& _token){
	std::string str = _token.str;
	std::map<std::string, SkinParser::TokenType>::iterator it;
	it = keywordMap.find(str);

	if(it != keywordMap.end()){ //token is a keyword
		//std::cout << "got keyword " << str << std::endl;
		return keywordMap[str];
	}
	else{ //token is some other type of token
		if(strIsNumber((char*)str.c_str())){
			//std::cout << "gtt: got num token " << str << std::endl;
			return numToken;
		}
		else if(str == "{"){
			//std::cout << "gtt: got { token" << std::endl;
			return openCurlyToken;
		}
		else if(str == "}"){
			//std::cout << "gtt: got } token" << std::endl;
			return closeCurlyToken;
		}
		else if(str == ""){
			//std::cout << "gtt: reached end of file" << std::endl;
			return endOfFile;
		}
		else{
			//std::cout << "gtt: got bad token " << str << std::endl;
			return badToken;
		}
	}
}

void SkinParser::parseTokens(const std::vector<Token>& _tokenList){
	TokenState currentState = start;
	Token currentToken = Token();
	TokenType currentTokenType;

	while(currentState != end){
		currentToken = getNextToken();
		currentTokenType = getTokenType(currentToken);
		if(currentTokenType != endOfFile){
			TokenState(SkinParser::*TokenFunc) (std::string&) = StateFunction[StateTable[currentTokenType][currentState]];
			currentState = (this->*TokenFunc)(currentToken.str);
		}
		else return;
	}
}

SkinParser::TokenState SkinParser::gotBadToken(std::string& _str){
	std::cout << "got bad token" << std::endl;
	return end;
}

SkinParser::TokenState SkinParser::gotPositionsKeyword(std::string& _str){
	//std::cout << "got position keyword" << std::endl;
	//output << "got position keyword" << std::endl;
	
	std::string numVertsToken = getNextToken().str;

	//check if string is valid number
	if(!strIsNumber((char*)numVertsToken.c_str())){
		std::cout << "invalid number token" << std::endl;
		output << "invalid number token" << std::endl;
		exit(1);
	}
	int numVerts = atoi(numVertsToken.c_str());

	checkForOpenCurly();

	float x, y, z;
	for(int i = 0; i < numVerts; i++){
		//std::cout << "make vert" << std::endl;
		//output << "make vert" << std::endl;
		x = atof(getNextToken().str.c_str());
		y = atof(getNextToken().str.c_str());
		z = atof(getNextToken().str.c_str());
		//std::cout << "vert x= " << x << " y= " << y << " z= " << z << std::endl;
		//output << "vert x= " << x << " y= " << y << " z= " << z << std::endl;
		Vertex vert = Vertex();
		vert.pos[0] = x;
		vert.pos[1] = y;
		vert.pos[2] = z;
		vert.pos[3] = 1;
		model.vertices.push_back(vert);
	}

	checkForCloseCurly();

	return afterPositionsKeyword;
}

SkinParser::TokenState SkinParser::gotNormalsKeyword(std::string& _str){
	//std::cout << "got normals keyword" << std::endl;
	//output << "got normals keyword" << std::endl;
	
	std::string numNormalsToken = getNextToken().str;
	if(atoi(numNormalsToken.c_str()) != model.vertices.size()){
		std::cout << "ERROR: num normals must be equal to num positions. Num normals is " << numNormalsToken << " num positions is " << model.vertices.size() << std::endl;
		output << "ERROR: num normals must be equal to num positions. Num normals is " << numNormalsToken << " num positions is " << model.vertices.size() << std::endl;
	}
	checkForOpenCurly();
	float x, y, z;
	for(int i = 0; i < model.vertices.size(); i++){
		//std::cout << "make vert" << std::endl;
		//output << "make vert" << std::endl;
		x = atof(getNextToken().str.c_str());
		y = atof(getNextToken().str.c_str());
		z = atof(getNextToken().str.c_str());
		//std::cout << "vert x= " << x << " y= " << y << " z= " << z << std::endl;
		//output << "vert x= " << x << " y= " << y << " z= " << z << std::endl;
		model.vertices[i].normals[0] = x;
		model.vertices[i].normals[1] = y;
		model.vertices[i].normals[2] = z;
		model.vertices[i].normals[3] = 0;
	}
	checkForCloseCurly();

	return afterNormalsKeyword;
}

SkinParser::TokenState SkinParser::gotSkinWeightsKeyword(std::string& _str){
	//std::cout << "got skin weights keyword" << std::endl;
	//output << "got skin weights keyword" << std::endl;

	std::string numSkinWeightsToken = getNextToken().str;
	if(atoi(numSkinWeightsToken.c_str()) != model.vertices.size()){
		std::cout << "ERROR: num normals must be equal to num positions. Num normals is " << numSkinWeightsToken << " num positions is " << model.vertices.size() << std::endl;
		output << "ERROR: num normals must be equal to num positions. Num normals is " << numSkinWeightsToken << " num positions is " << model.vertices.size() << std::endl;
	}
	checkForOpenCurly();

	std::string numAttachmentsToken;
	int numAttachments;
	int index;
	float weight;
	for(int i = 0; i < model.vertices.size(); i++){
		numAttachmentsToken = getNextToken().str;
		numAttachments = atoi(numAttachmentsToken.c_str());
		//std::cout << "num attachments " << numAttachments << std::endl;
		//output << "num attachments " << numAttachments << std::endl;
		for(int j = 0; j < numAttachments; j++){
			index = atoi(getNextToken().str.c_str());
			//std::cout << "got index " << index << std::endl;
			//output << "got index " << index << std::endl;
			weight = atof(getNextToken().str.c_str());
			//std::cout << "got weight " << weight << std::endl;
			//output << "got weight " << weight << std::endl;
			Vertex::JointWeight jointWeight = Vertex::JointWeight(index, weight);
			model.vertices[i].weights.push_back(jointWeight);
		}
	}
	checkForCloseCurly();

	checkSkinWeights();
	
	return afterSkinWeightsKeyword;
}

void SkinParser::checkSkinWeights(){
	
	float weightSum = 0.0f;
	for(int i = 0; i < model.vertices.size(); i++){
		for(int j = 0; j < model.vertices[i].weights.size(); j++){
			weightSum += model.vertices[i].weights[j].weight;
		}
		
		if(weightSum != 1.0f){
			std::cout << "ERROR: weights for vertex " << i << " do not add to 1. weightSum = " << weightSum << std::endl;
		}
		weightSum = 0.0f;
	}
}

SkinParser::TokenState SkinParser::gotTrianglesKeyword(std::string& _str){
	//std::cout << "got triangles keyword" << std::endl;
	std::string numTrianglesToken = getNextToken().str;
	int numTriangles = atoi(numTrianglesToken.c_str());
	checkForOpenCurly();
	
	for(int i = 0; i < numTriangles; i++){
		Triangle tri;
		tri.verts[0] = atoi(getNextToken().str.c_str());
		tri.verts[1] = atoi(getNextToken().str.c_str());
		tri.verts[2] = atoi(getNextToken().str.c_str());
		model.triangles.push_back(tri);
	}
	checkForCloseCurly();
	//model.printTriangles();
	return afterTrianglesKeyword;
}

SkinParser::TokenState SkinParser::gotBindingsKeyword(std::string& _str){
	//std::cout << "got bindings keyword" << std::endl;
	std::string numBindingsToken = getNextToken().str;
	int numBindings = atoi(numBindingsToken.c_str());
	
	//TODO:
	////if(numBindings != numJoints) ERRROOR!!!!!
	checkForOpenCurly();
	
	std::string next;
	for(int i = 0; i < numBindings; i++){
		next = getNextToken().str;
		if(next == "matrix"){
			gotMatrixKeyword(i);
		}
		else{
			gotBadToken(next);
		}
	}
	checkForCloseCurly();
	//model.printBindings();
	return end;
}

SkinParser::TokenState SkinParser::gotMatrixKeyword(int _jointNumber){
	//std::cout << "got matrix keyword" << std::endl;

	float row0[4] = { 0, 0, 0, 0 };
	float row1[4] = { 0, 0, 0, 0 };
	float row2[4] = { 0, 0, 0, 0 };
	float row3[4] = { 0, 0, 0, 1 };
	Matrix4 matrix;

	checkForOpenCurly();
	row0[0] = atof(getNextToken().str.c_str());
	row0[1] = atof(getNextToken().str.c_str());
	row0[2] = atof(getNextToken().str.c_str());

	row1[0] = atof(getNextToken().str.c_str());
	row1[1] = atof(getNextToken().str.c_str());
	row1[2] = atof(getNextToken().str.c_str());

	row2[0] = atof(getNextToken().str.c_str());
	row2[1] = atof(getNextToken().str.c_str());
	row2[2] = atof(getNextToken().str.c_str());

	row3[0] = atof(getNextToken().str.c_str());
	row3[1] = atof(getNextToken().str.c_str());
	row3[2] = atof(getNextToken().str.c_str());

	matrix.setRow(0, row0);
	matrix.setRow(1, row1);
	matrix.setRow(2, row2);
	matrix.setRow(3, row3);

	//model.bindings.push_back(matrix);
	tree<BallJoint>::iterator it;
	it = getJointByIndex(_jointNumber);
	it->binding = matrix;

	checkForCloseCurly();
	return afterMatrixKeyword;
}

tree<BallJoint>::iterator& SkinParser::getJointByIndex(int _index){
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

SkinParser::TokenState SkinParser::gotNumToken(std::string& _str){
	//std::cout << "got num token" << std::endl;
	return afterNumToken;
}

SkinParser::TokenState SkinParser::gotOpenCurlyToken(std::string& _str){
	//std::cout << "got open curly token" << std::endl;
	return afterOpenCurlyToken;
}
SkinParser::TokenState SkinParser::gotCloseCurlyToken(std::string& _str){
	//std::cout << "got close curly token" << std::endl;
	return afterOpenCurlyToken;
}

Model SkinParser::getModel(){
	return model;
}

bool SkinParser::strIsNumber(char* buff)
{
	int mybool;
	int len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		mybool = isdigit(*buff++);

		if(!mybool)
		{
			return 0;
		}
	}

	return 1;
}

void SkinParser::checkForOpenCurly(){
	std::string next = getNextToken().str; //this token should always be an opening brace, any other token types are invalid in this state
	if(next == "{"){
		//std::cout << "got open curly token" << std::endl;
		//output << "got open curly token" << std::endl;
		gotOpenCurlyToken(next);
	}
	else{
		gotBadToken(next);
	}
}

void SkinParser::checkForCloseCurly(){
	std::string next = getNextToken().str; //this token should always be an closing brace, any other token types are invalid in this state
	if(next == "}"){
		gotCloseCurlyToken(next);
	}
	else{
		gotBadToken(next);
	}
}

void SkinParser::printTree(){
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