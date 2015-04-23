
#ifndef SKIN_PARSER_H
#define SKIN_PARSER_H

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "tree.hh"
#include "BallJoint.h"
#include "Model.h"
#include "Triangle.h"

/*
* The skin parser class takes a .skin file and generates a model from it
*/
class SkinParser{

public:
	SkinParser();
	SkinParser(const std::vector<std::string>& _tokenList, tree<BallJoint>& _tree, int _numJoints);
	SkinParser(const SkinParser& _sp);
	SkinParser& operator =(SkinParser _sp);
	~SkinParser();

	enum TokenState{
		afterEOF = -1,
		start,						//0
		afterPositionsKeyword,		//1
		afterNormalsKeyword,		//2
		afterSkinWeightsKeyword,	//3
		afterTrianglesKeyword,		//4
		afterBindingsKeyword,		//5
		afterMatrixKeyword,			//6
		afterNumToken,				//7
		afterOpenCurlyToken,		//8
		afterCloseCurlyToken,		//9
		end,						//10
		numStates
	};

	enum TokenType{ badToken,
					positionsKeyword,
					normalsKeyword,
					skinWeightsKeyword,
					trianglesKeyword,
					bindingsKeyword,
					matrixKeyword,
					numToken,
					openCurlyToken,
					closeCurlyToken,
					endOfFile,
					numTokenTypes
	};

	//typedefs
	typedef unsigned char uchar;
	typedef unsigned int uint;
	typedef int State;
	typedef TokenState(SkinParser::*TokenFunc) (std::string&);

	class Token{
	public:
		std::string str;
		SkinParser::TokenType type;
		Token(){}
		Token(std::string& _str){ str = _str; };
		Token(const Token& _token) : str(_token.str), type(_token.type){}
		~Token(){}
		void setType(SkinParser::TokenType _type){ type = _type; }
	};

	static uchar StateTable[numTokenTypes][numStates];
	void parseTokens(const std::vector<Token>& _tokenList);
	static TokenFunc StateFunction[];
	TokenType getTokenType(Token& _token);
	Token getNextToken();
	bool strIsNumber(char* buff);
	void checkSkinWeights();

	TokenState gotBadToken				(std::string& _str);
	TokenState gotPositionsKeyword		(std::string& _str);
	TokenState gotNormalsKeyword		(std::string& _str);
	TokenState gotSkinWeightsKeyword	(std::string& _str);
	TokenState gotTrianglesKeyword		(std::string& _str);
	TokenState gotBindingsKeyword		(std::string& _str);
	TokenState gotMatrixKeyword			(int _jointNumber );
	TokenState gotNumToken				(std::string& _str);
	TokenState gotOpenCurlyToken		(std::string& _str);
	TokenState gotCloseCurlyToken		(std::string& _str);

	void checkForOpenCurly();
	void checkForCloseCurly();

	Model getModel();
	tree<BallJoint>::iterator& getJointByIndex(int _index);
	void SkinParser::printTree();

	

private:
	int numJoints;
	tree<BallJoint> skelTree;
	Model model;
	std::vector<std::string> strList;
	std::vector<Token> tokenList;
	std::map<std::string, TokenType> keywordMap;
	std::ofstream output;

};

#endif