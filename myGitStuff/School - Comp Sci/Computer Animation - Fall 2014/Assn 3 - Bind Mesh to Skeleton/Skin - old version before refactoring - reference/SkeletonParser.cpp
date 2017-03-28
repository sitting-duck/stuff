#include <iostream>
#include <regex>
#include "SkeletonParser.h"
#include "tree.hh"
#include "tree_util.hh"
#include "BallJoint.h"

typedef unsigned int uint;
class Token;

SkeletonParser::TokenFunc SkeletonParser::StateFunction[] = { 
	&SkeletonParser::gotBadToken,				//0
	&SkeletonParser::gotBallJointToken,			//1
	&SkeletonParser::gotBallJointNameToken,		//2
	&SkeletonParser::gotOffsetToken,			//3
	&SkeletonParser::gotBoxminToken,			//4
	&SkeletonParser::gotBoxMaxToken,			//5
	&SkeletonParser::gotPoseToken,				//6
	&SkeletonParser::gotNumToken,				//7
	&SkeletonParser::gotRotXLimitToken,			//8
	&SkeletonParser::gotRotYLimitToken,			//9
	&SkeletonParser::gotRotZLimitToken,			//10
	&SkeletonParser::gotOpenCurlyToken,			//11
	&SkeletonParser::gotCloseCurlyToken,		//12
	&SkeletonParser::gotEOFToken				//13
};

SkeletonParser::uchar SkeletonParser::StateTable[SkeletonParser::numTokenTypes][SkeletonParser::numStates] = {  
	//						start    afterBallJointToken    afterBallJointNameToken    afterOpenCurlyToken    afterOffsetToken    afterBoxminToken    afterBoxMaxToken    afterRotXLimitToken    afterRotYLimitToken    afterRotZLimitToken    afterNumToken    afterPoseToken    afterCloseCurlyToken    afterEOFToken
	/*badToken*/			{ 0,			  0,						0,						0,					  0,					0,				0,						0,						0,					0,					0,					0,					0,					0},
	/*ballJointToken*/		{ 1,			  0,						0,						0,					  1,					1,				1,						1,						1,					1,					1,					1,					1,					0},
	/*ballJointNameToken*/	{ 0,			  2,						0,						0,					  0,					0,				0,						0,						0,					0,					0,					0,					0,					0},
	/*offsetToken*/			{ 0,			  0,						0,						3,					  0,					0,				0,						0,						0,					0,					3,					0,					0,					0},
	/*boxminToken*/			{ 0,			  0,						0,						4,					  4,					4,				4,						4,						4,					4,					4,					4,					0,					0},
	/*boxMaxToken*/			{ 0,			  0,						0,						5,					  5,					5,				5,						5,						5,					5,					5,					5,					0,					0},
	/*poseToken*/			{ 0,			  0,						0,						6,					  6,					6,				6,						6,						6,					6,					6,					6,					0,					0},
	/*numToken*/			{ 0,			  0,						0,						0,					  7,					7,				7,						7,						7,					7,					7,					7,					0,					0},
	/*rotXLimitToken*/		{ 0,			  0,						0,						8,					  8,					8,				8,						8,						8,					8,					8,					8,					0,					0},
	/*rotYLimitToken*/		{ 0,			  0,						0,						9,					  9,					9,				9,						9,						9,					9,					9,					9,					0,					0},
	/*rotZLimitToken*/		{ 0,			  0,						0,						10,					  10,					10,				10,						10,						10,					10,					10,					10,					0,					0},
	/*openCurlyToken*/		{ 0,			  0,						11,						0,					  0,					0,				0,						0,						0,					0,					0,					0,					0,					0},
	/*closeCurlyToken*/		{ 0,			  0,						0,						12,					  12,					12,				12,						12,						12,					12,					12,					12,					12,					0},
	/*endOfFile*/			{ 0,			  0,						0,						0,					  0,					0,				0,						0,						0,					0,					0,					0,					0,					0} 
	};

SkeletonParser::SkeletonParser(){}
SkeletonParser::~SkeletonParser(){}

SkeletonParser::SkeletonParser(const std::vector<std::string>& _tokenList) : strList(_tokenList), numOpenCurlies(0){
	numBallJoints = 0;
	for(uint i = 0; i < strList.size(); i++){
		auto token = Token(strList[i]);
		tokenList.push_back(token);
	}

	keywordTypeMap["balljoint"] = ballJointToken;
	keywordTypeMap["offset"]	= offsetToken;
	keywordTypeMap["boxmin"]	= boxminToken;
	keywordTypeMap["boxmax"]	= boxMaxToken;
	keywordTypeMap["rotxlimit"] = rotXLimitToken;
	keywordTypeMap["rotylimit"] = rotYLimitToken;
	keywordTypeMap["rotzlimit"] = rotZLimitToken;
	keywordTypeMap["pose"]		= poseToken;

	parseTokens(tokenList);
	//printTree();
}

void SkeletonParser::parseTokens(const std::vector<Token>& _tokenList){
	TokenState currentState = start; 
	Token currentToken = Token();
	TokenType currentTokenType;
	
	while(currentState != end){
		currentToken = getNextToken();
		currentTokenType = getTokenType(currentToken);
		if(currentTokenType != endOfFile){
			TokenState(SkeletonParser::*TokenFunc) (std::string&) = StateFunction[StateTable[currentTokenType][currentState]];
			currentState = (this->*TokenFunc)(currentToken.str);
		}
		else return;
	} 
}

void SkeletonParser::printTree(){
	tree<BallJoint>::iterator it, end;
	tree<BallJoint>::sibling_iterator sib;
	tree<BallJoint>::fixed_depth_iterator fdi, fdi_end;

	it = tr.begin();
	//std::cout << "begin: " << it->getName() << std::endl;
	end = tr.end();
	//std::cout << "end: " << end->getName() << std::endl;
	int maxDepth = tr.max_depth();
	//std::cout << "max depth: " << maxDepth << std::endl;

	for (int i = 0; i < tr.max_depth() + 1; i++){
		fdi = tr.begin_fixed(tr.begin(), i);
		//fdi_end = tr.end_fixed(tr.begin(), i);
		
		//print dat level tho
		while (tr.is_valid(fdi)){
			std::cout << fdi->getName() << " ";
			fdi++;
		}
		std::cout << std::endl;
	}
}

SkeletonParser::TokenType SkeletonParser::getTokenType(SkeletonParser::Token& _token){
	std::string str = _token.str;
	std::map<std::string, SkeletonParser::TokenType>::iterator it;
	it = keywordTypeMap.find(str);

	std::regex number_regex( R"(-?\d+(\.\d+)?)" );
	std::regex var_name_regex( R"([a-zA-Z_][a-zA -Z_\d]*)" );

	if(it != keywordTypeMap.end()){ //token is a keyword
		//std::cout << "got keyword " << str << std::endl;
		return keywordTypeMap[str];
	}
	else{ //token is some other type of token
		//if(regex_search(str, number_regex)){
		//	std::cout << "gtt: got num token " << str << std::endl;
		//	return numToken;
		//}
		if(strIsNumber((char*)str.c_str())){
			//std::cout << "gtt: got num token " << str << std::endl;
			return numToken;
		}
		else
			if(regex_search(str, var_name_regex)){
			//std::cout << "gtt: got var name token " << str << std::endl;
			return ballJointNameToken;
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

SkeletonParser::Token SkeletonParser::getNextToken(){
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

void SkeletonParser::printLevelOrderTree(){
	
	tree<BallJoint>::iterator top, loc;
	tree<BallJoint>::sibling_iterator sib;

	top = tr.begin();
	loc = tr.begin();
	sib = tr.begin();

	//if we have no reached the last node
	if (loc != tr.end()){
		//sib = tr.begin(loc);

		//if there is only one node we just print that one node and go to the next level
		if (sib == tr.end(loc)){
			std::cout << (sib.node->data.getName()) << std::endl;
			return;
		}
		else{
			while (loc != tr.end()){

				//print dat level tho
				while (sib != tr.end(loc)){
					std::cout << (sib.node->data.getName()) << std::endl;
					sib++;
				}
				//go to the next level
				loc++;
			}
			
		}
	}
}

SkeletonParser::TokenState SkeletonParser::gotBadToken(std::string& _str){
	std::cout << "got bad token" << std::endl;
	return end;
}

SkeletonParser::TokenState SkeletonParser::gotBallJointToken		 (std::string& _str){
	return afterBallJointToken;
}

SkeletonParser::TokenState SkeletonParser::gotBallJointNameToken	 (std::string& _str){
	BallJoint joint = BallJoint(_str);
	numBallJoints++;
	if(tr.size() == 0){
		//then we put this new joint at the root
		tr.set_head(joint);
		//std::cout << "set root to joint named: " << joint.getName() << std::endl;
		currentNode = tr.begin();
		Matrix4 dummyMatrix;
		dummyMatrix.identity();
		currentNode->calculateWorld(dummyMatrix);
	}
	else{
		//std::cout << "added joint " << joint.getName() << std::endl;
		currentNode = tr.append_child(currentNode, joint);
	}
	return afterBallJointNameToken;
}

SkeletonParser::TokenState SkeletonParser::gotOffsetToken		 (std::string& _str){
	//BallJoint joint = tr.
	//std::cout << "got offset token" << std::endl;
	Token token;
	double num;
	for(int i = 0; i < currentNode->getDOF(); i++){
		token = getNextToken();
		num = atof(token.str.c_str());
		currentNode->offset[i] = num;
		//std::cout << "offset[" << i << "] = " << num << std::endl;
	}	
	return afterOffsetToken;
}

SkeletonParser::TokenState SkeletonParser::gotBoxminToken		 (std::string& _str){
	//std::cout << "got boxmin token" << std::endl;
	Token token;
	double num;
	for(int i = 0; i < currentNode->getDOF(); i++){
		token = getNextToken();
		num = atof(token.str.c_str());
		currentNode->boxmin[i] = num;
		//std::cout << "boxmin[" << i << "] = " << num << std::endl;
	}
	return afterBoxminToken;
}

SkeletonParser::TokenState SkeletonParser::gotBoxMaxToken		 (std::string& _str){
	//std::cout << "got boxmax token" << std::endl;
	Token token;
	double num;
	for(int i = 0; i < currentNode->getDOF(); i++){
		token = getNextToken();
		num = atof(token.str.c_str());
		currentNode->boxmax[i] = num;
		//std::cout << "boxmax[" << i << "] = " << num << std::endl;
	}
	return afterBoxMaxToken;
}

SkeletonParser::TokenState SkeletonParser::gotPoseToken			 (std::string& _str){
	//std::cout << "got pose token" << std::endl;
	Token token;
	double num;
	for(int i = 0; i < currentNode->getDOF(); i++){
		token = getNextToken();
		num = atof(token.str.c_str());
		currentNode->pose[i] = num;
		//std::cout << "pose[" << i << "] = " << num << std::endl;
	}
	return afterPoseToken;
}

SkeletonParser::TokenState SkeletonParser::gotNumToken			 (std::string& _str){
	return afterNumToken;
}

SkeletonParser::TokenState SkeletonParser::gotRotXLimitToken		 (std::string& _str){
	//std::cout << "got RotXLimitToken token" << std::endl;
	Token token;
	double num;
	for(int i = 0; i < 2; i++){
		token = getNextToken();
		num = atof(token.str.c_str());
		currentNode->rotlimit[0][i] = num;
		//std::cout << "rotlimit[0][" << i << "] = " << num << std::endl;
	}
	return afterRotXLimitToken;
}

SkeletonParser::TokenState SkeletonParser::gotRotYLimitToken		 (std::string& _str){
	//std::cout << "got RotYLimitToken token" << std::endl;
	Token token;
	double num;
	for(int i = 0; i < 2; i++){
		token = getNextToken();
		num = atof(token.str.c_str());
		currentNode->rotlimit[1][i] = num;
		//std::cout << "rotlimit[1][" << i << "] = " << num << std::endl;
	}
	return afterRotYLimitToken;
}

SkeletonParser::TokenState SkeletonParser::gotRotZLimitToken		 (std::string& _str){
	//std::cout << "got RotZLimitToken token" << std::endl;
	Token token;
	double num;
	for(int i = 0; i < 2; i++){
		token = getNextToken();
		num = atof(token.str.c_str());
		currentNode->rotlimit[2][i] = num;
		//std::cout << "rotlimit[2][" << i << "] = " << num << std::endl;
	}
	return afterRotZLimitToken;
}

SkeletonParser::TokenState SkeletonParser::gotOpenCurlyToken		 (std::string& _str){
	numOpenCurlies++;
	return afterOpenCurlyToken;
}

SkeletonParser::TokenState SkeletonParser::gotCloseCurlyToken	 (std::string& _str){
	numOpenCurlies--;
	//calculateJoint();
	currentNode = tr.parent(currentNode);

	return afterCloseCurlyToken;
}

SkeletonParser::TokenState SkeletonParser::gotEOFToken(std::string& _str){
	return end;
}

void SkeletonParser::calculateJoint(){
	
	currentNode->calulcateLocal();
	//std::cout << "got from calcLocal " << std::endl;
	//std::cout << currentNode->local << std::endl;

	if(currentNode == tr.begin()){
		currentNode->world = currentNode->local;
	}
	else{
		//std::cout << "in caljoint, I am " << currentNode->name << " my parent is " << tr.parent(currentNode)->name << std::endl;
		currentNode->calculateWorld((tr.parent(currentNode))->world);
		//std::cout << "got from calcWorld " << std::endl;
		//std::cout << currentNode->world << std::endl;
	}
}

void SkeletonParser::calculateJoint(tree<BallJoint>::iterator& _currentNode){
	
	if(_currentNode->hasBeenCalc == false){
		//std::cout << "in calc joint" << std::endl;
		_currentNode->calulcateLocal();
		//std::cout << "got from calcLocal " << std::endl;
		//std::cout << _currentNode->local << std::endl;

		//std::cout << "tr.begin() " << tr.begin()->name << std::endl;

		if(_currentNode->name == tr.begin()->name){
			_currentNode->world = _currentNode->local;
		}
		else{
			//std::cout << "in caljoint, I am " << _currentNode->name << " my parent is " << tr.parent(_currentNode)->name << std::endl;
			_currentNode->calculateWorld((tr.parent(_currentNode))->world);
			
			std::cout << "joint " << _currentNode->index << " world " << std::endl;
			std::cout << _currentNode->world << std::endl;
			//std::cout << "got from calcWorld " << std::endl;
			//std::cout << _currentNode->world << std::endl;
		}
		_currentNode->hasBeenCalc = true;
	}
	else{
		return;
	}
	
}

bool SkeletonParser::strIsNumber(char* buff)
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

tree<BallJoint>::iterator& SkeletonParser::getJointByIndex(int _index){
	tree<BallJoint>::pre_order_iterator it;
	it = tr.begin();
	while(it != tr.end()){
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