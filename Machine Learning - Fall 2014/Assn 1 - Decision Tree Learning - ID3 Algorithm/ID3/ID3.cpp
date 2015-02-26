#include "ID3.h"
#include <iostream>
#include<fstream>
#include <cmath>
#include <algorithm>
#include <cstring>

ID3::ID3():tree(NULL)
{
	ID3("train.dat", "test.dat");
}

ID3::ID3(string _trainingFile, string _testingFile)
{
	getExamplesFromFile(_trainingFile, trainingAttrs);
	//getExamplesFromFile(_testingFile, testingAttrs);

	tree = new BinaryTree();
	createTree(lines, trainingAttrs);
	tree->printLevelOrderTree();
}

ID3::~ID3(){}
/**
* The target attribute refers to class.
* The attrList refers to all the other attributes
* _examples refers to the set of training data. _examples will be cut down as we move down the tree
*/
void ID3::createTree(vector<string>& _examples, vector<Attribute>& _attrList){

	static int round = 0;

	//if this is the first recursive call to createTree, then we will check for edge cases
	if (round == 0){
		//if an edge case was true, we do not continue creating the tree, the edge case was created in the edgeCases_CreateTree function
		if (edgeCases_CreateTree(_examples, _attrList)){
			return;
		}
	}
	

	


	/*double iGain, bestIgain;
	int bestAttr;
	for (int i = 0; i < trainingAttrs.size(); i++){
		iGain = -1;
		bestIgain = -1;
		bestAttr = -1;
		iGain = calculateInformationGain(trainingAttrs[i]);

	}*/
	round++;
}

bool ID3::allTrue(const vector<string>& _examples){
	//note we don't start at zero because we don't care about the attribute name line
	cout << "allTrue" << endl;
	for (int i = 1; i < _examples.size(); i++){
		//cout << _examples[i] << endl;
		if(_examples[i].back() == '0'){
			return false;
		}
	}
	return true;
}

bool ID3::allFalse(const vector<string>& _examples){
	//note we don't start at zero because we don't care about the attribute name line
	for (int i = 1; i < _examples.size(); i++){
		if (_examples[i].back() == '1'){
			return false;
		}
	}
	return true;
}

/**
* This function return the most common value for the class attribute in a set of examples.
* returns 1 if true is most common.
* returns 0 if false is most common.
* returns -1 if true and false are equally common
*/
int ID3::mostFrequentClassValue(const vector<string>& _examples){
	int numTrue, numFalse = 0;
	for (int i = 0; i < _examples.size(); i++){
		if (_examples[i].back() == '1'){
			numTrue++;
		}
		else{
			numFalse++;
		}
	}
	if (max(numTrue, numFalse) == numTrue){ return 1; }
	else if (max(numTrue, numFalse) == numFalse){ return 0; }
	else return -1;
}

bool ID3::edgeCases_CreateTree(const vector<string>& _examples, const vector<Attribute>& _attrList){
	if (_examples.size() == 0){
		tree->root = Node("empty tree");
		return true;
	}
	else if (allTrue(_examples)){
		tree->root = Node();
		tree->root.attribute.name.assign("1");
		return true;
	}
	else if (allFalse(_examples)){
		tree->root = Node("0");
		return true;
	}

	if (_attrList.size() == 0){
		if (mostFrequentClassValue(_examples) == 0){
			tree->root = Node("0");
			return true;
		}
		else if (mostFrequentClassValue(_examples) == 1){
			tree->root = Node("1");
			return true;
		}
		else{
			tree->root = Node("No tree can be generated from this data. There are no asttributes and no most common class value.");
			return true;
		}
	}
	return false;
}

void ID3::getExamplesFromFile(string& _fileName, vector<Attribute>& _attrList)
{
	ifstream ifs;
	ifs.open(_fileName, ios::in | ios::binary);
	
	//we grab the first line and populate attributes list
	vector<string> tokenLine;
	tokenLine = getTokenLine(ifs);
	for (int i = 0; i < tokenLine.size() - 1; i++){
		_attrList.push_back(Attribute(tokenLine[i]));
	}

	while (!ifs.eof()){
		tokenLine = getTokenLine(ifs);
		if (!(tokenLine[0] == "0" || tokenLine[0] == "1")){ break; }		
		cout << endl;
		for (int i = 0; i < tokenLine.size()-1; i++){
			if ((*(tokenLine[i].c_str())) == '0'){
				_attrList[i].numFalse++;
			}
			else{
				_attrList[i].numTrue++;
			}			
		}
		populateAttrsWithClassValues(tokenLine, _attrList);
	}
	lines.pop_back();
	//printAttrList(_attrList);
	printLines();
}

void ID3::printAttrList(vector<Attribute>& _attrList){
	for (int i = 0; i < _attrList.size(); i++){
		cout << _attrList[i].name;
		cout << " nt: " << _attrList[i].numTrue;
		cout << " ntt: " << _attrList[i].numTrueTrue;
		cout << " ntf: " << _attrList[i].numTrueFalse;
		cout << " nf: " << _attrList[i].numFalse;
		cout << " nft: " << _attrList[i].numFalseTrue;
		cout << " nff: " << _attrList[i].numFalseFalse << endl;
	}
}

void ID3::printLines(){
	cout << "lines: " << endl;
	for (int i = 0; i < lines.size(); i++){
		cout << lines[i] << endl;
	}
	cout << endl;
}

void ID3::printTokenLine(vector<string>& _tokenLine){
	for (int i = 0; i < _tokenLine.size(); i++){
		cout << " " << _tokenLine[i] << " ";
	}
	cout << endl;
}

void ID3::populateAttrsWithClassValues(vector<string>& _tokenArray, vector<Attribute>& _attrList){
	
	char classValue = *(_tokenArray[_tokenArray.size() - 1].c_str());

	char attrValue;

	for (int i = 0; i < _attrList.size(); i++){
		attrValue = *_tokenArray[i].c_str();
		if (attrValue == '0' && classValue == '0'){
			_attrList[i].numFalseFalse++;
		}
		else if (attrValue == '1'&& classValue == '0'){
			_attrList[i].numTrueFalse++;
		}
		else if (attrValue == '0' && classValue == '1'){
			_attrList[i].numFalseTrue++;
		}
		else if (attrValue == '1' && classValue == '1'){
			_attrList[i].numTrueTrue++;
		}
		else{ cout << "Error: invalid token" << endl; }
	}
}

vector<string> ID3::getTokenLinee(ifstream& _ifs){
	
	vector<string> tokenList;
	string token;
	string line;
	char c = ' ';
	int eof = _ifs.peek();
	int index = 0;

	while (c != '\n' || _ifs.good() ){
		c = (char)_ifs.get();
		if (c == ' ' || c == '\t'){
			tokenList.push_back(token);
			token = "";			
		}
		else if( c == '\n'){ // we;ve reached the end of the line
			tokenList.push_back(token);
			line.pop_back();
			cout << "line to push: " << line << " line size: " << line.size() << endl;
			lines.push_back(line);
			line = "";
			return tokenList;
		}
		else if (c == EOF){
			return tokenList;
		}
		else{
			token.append(1, c);
			line.append(1, c);
		}
		index++;
	}
	return tokenList;
}

vector<string> ID3::getTokenLine(ifstream& _ifs){
	vector<string> tokenList;
	string buf;
	getline(_ifs, buf);
	char* pch;
	char* gotString = new char[buf.size() + 1];
	strcpy(gotString, buf.c_str());
	gotString[buf.size()] = '\0';
	cout << "got string: " << gotString << endl;
	
	pch = strtok(gotString, " \n\t");
	while (pch != NULL){
		tokenList.push_back(string(pch));
		pch = strtok(NULL, " \n\t");
	}

	cout << "test token line: " << endl;
	for (int i = 0; i < tokenList.size(); i++){
		cout << tokenList[i] << " size: " << tokenList[i].size() << endl;
	}
	cout << endl;
		delete [] gotString;

		return tokenList;
}

double ID3::calculateEntropy(Attribute& _attribute){
	int numTrue = _attribute.numTrue;
	int numFalse = _attribute.numFalse;
	int numValues = numTrue + numFalse;

	double ratioTrue = numTrue / numValues;
	double ratioFalse = _attribute.numFalse / numValues;

	double trueAttribute = (ratioTrue)*(log2(ratioTrue));
	double falseAttribute = (ratioFalse)*(log2(ratioFalse));
	double entropy = (-1)*((trueAttribute)+(falseAttribute));
	
	if (entropy > 1.0 || entropy < 0.0){ cout << "Invalid Entropy value!!!" << endl; }
	return entropy;
}

double calculateConditionalEntropy(Attribute _attribute){

	

	int numTrue = _attribute.numTrue;
	int numFalse = _attribute.numFalse;
	int totalNum = numTrue + numFalse;

	double numTrueTrue = _attribute.numTrueTrue;
	double numTrueFalse = _attribute.numTrueFalse;
	double numFalseTrue = _attribute.numFalseTrue;
	double numFalseFalse = _attribute.numFalseFalse;

	double ratioTrueTrue = numTrueTrue / numTrue;
	double ratioTrueFalse = numTrueFalse / numTrue;
	double ratioFalseTrue = numFalseTrue / numFalse;
	double ratioFalseFalse = numFalseFalse / numFalse;

	double ratioTrue = _attribute.numTrue / totalNum;
	double ratioFalse = _attribute.numFalse / totalNum;

	double trueTrueEntropy = ratioTrueTrue*(log2(ratioTrueTrue));
	double trueFalseEntropy = ratioTrueFalse*(log2(ratioTrueFalse));
	double falseTrueEntropy = ratioFalseTrue*(log2(ratioFalseTrue));
	double falseFalseEntropy = ratioFalseFalse*(log2(ratioFalseFalse));

	double trueAttribute = ratioTrue*(trueTrueEntropy + trueFalseEntropy);
	double falseAttribute = ratioFalse*(falseTrueEntropy + falseFalseEntropy);

	double conditionalEntropy = (-1)*(trueAttribute + falseAttribute);
	if (conditionalEntropy < 0 || conditionalEntropy > 1){ cout << "Invalid conditional entropy value" << endl; }
	return conditionalEntropy;
}



double ID3::calculateInformationGain(Attribute& _attribute){
	//double informationGain = calculateEntropy(_attribute) - calculateConditionalEntropy(_attribute);
	double informationGain = calculateEntropy(_attribute) - calculateConditionalEntropy(_attribute);
	return informationGain;
}
