
#ifndef TREE_FACTORY_H
#define TREE_FACTORY_H

#include <vector>
#include <string>
#include <functional>
#include <map>
#include "tree.hh"
#include "tree_util.hh"
#include "BallJoint.h"

class Token;

class SkeletonParser{

public:
	enum TokenState {
		afterEOF = -1,
		start,
		afterBallJointToken,
		afterBallJointNameToken,
		afterOpenCurlyToken,
		afterOffsetToken,
		afterBoxminToken,
		afterBoxMaxToken,
		afterRotXLimitToken,
		afterRotYLimitToken,
		afterRotZLimitToken,		
		afterNumToken,
		afterPoseToken,
		afterCloseCurlyToken,
		end,
		numStates
	};

	//typedefs
	typedef unsigned char uchar;
	typedef unsigned int uint;
	typedef int State;
	typedef TokenState (SkeletonParser::*TokenFunc) (std::string&);

	SkeletonParser();
	~SkeletonParser();
	SkeletonParser(const std::vector<std::string>& _tokenList );

	void printLevelOrderTree();
	void printTree();

	enum TokenType{ badToken,
					ballJointToken,
					ballJointNameToken, 
					offsetToken, 
					boxminToken, 
					boxMaxToken, 
					poseToken, 
					numToken,
					rotXLimitToken,
					rotYLimitToken, 
					rotZLimitToken,
					openCurlyToken,
					closeCurlyToken,
					endOfFile,
					numTokenTypes};

	class Token{
	public:
		std::string str;
		SkeletonParser::TokenType type;
		
		Token(){}
		Token(std::string& _str){ str = _str; };
		Token(const Token& _token): str(_token.str), type(_token.type){}
		~Token(){}
		void setType(SkeletonParser::TokenType _type){ type = _type; }
	};

	static uchar StateTable[numTokenTypes][numStates];

	void parseTokens(const std::vector<Token>& _tokenList);
	static TokenFunc StateFunction[];
	void setType(TokenType _type);
	TokenType getTokenType(Token& _token);
	Token getNextToken();

	TokenState gotBadToken( std::string& _str);
	TokenState gotBallJointToken( std::string& _str);
	TokenState gotBallJointNameToken( std::string& _str);
	TokenState gotOffsetToken( std::string& _str);
	TokenState gotBoxminToken( std::string& _str);
	TokenState gotBoxMaxToken( std::string& _str);
	TokenState gotPoseToken( std::string& _str);
	TokenState gotNumToken( std::string& _str);
	TokenState gotRotXLimitToken( std::string& _str);
	TokenState gotRotYLimitToken( std::string& _str);
	TokenState gotRotZLimitToken( std::string& _str);
	TokenState gotOpenCurlyToken( std::string& _str);
	TokenState gotCloseCurlyToken( std::string& _str);
	TokenState gotEOFToken(std::string& _str);
	
	tree<BallJoint>& getTree();
	void calculateJoint();
	void calculateJoint(tree<BallJoint>::iterator& _currentNode);
	bool strIsNumber(char* buff);
	tree<BallJoint>::iterator& getJointByIndex(int _index);

	uint numBallJoints;
	tree<BallJoint> tr;

private:
	
	tree<BallJoint>::iterator currentNode;

	std::vector<std::string> strList;
	std::vector<Token> tokenList;
	std::hash<std::string> keywordHash;
	std::map<std::string, TokenType> keywordTypeMap;
	uint numOpenCurlies;
	
};

inline void SkeletonParser::setType(SkeletonParser::TokenType _type){
	
}

inline tree<BallJoint>& SkeletonParser::getTree(){ return tr; }

#endif
