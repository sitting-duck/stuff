#ifndef ID3_H
#define ID3_H

#include <vector>
#include "Attribute.h"
#include "BinaryTree.h"

using namespace std;

class ID3{

public:
	vector<Attribute> trainingAttrs;
	vector<Attribute> testingAttrs;
	vector<string> lines;

	BinaryTree* tree;


	ID3();
	ID3(string _trainingFile, string _testingFile);
	~ID3();

	void getExamplesFromFile(string& _fileName, vector<Attribute>& _attrList);
	void createTree(vector<string>& _examples, vector<Attribute>& _attrList);
	double calculateInformationGain(Attribute& _attribute);
	double calculateEntropy(Attribute& _attribute);

	vector<string> ID3::getTokenLine(ifstream& _ifs);
	vector<string> ID3::getTokenLinee(ifstream& _ifs);
	void populateAttrsWithClassValues(vector<string>& _tokenArray, vector<Attribute>& _attrList);
	void printAttrList(vector<Attribute>& _attrList);
	void printTokenLine(vector<string>& _tokenLine);
	void printLines();
	bool allTrue(const vector<string>& _examples);
	bool allFalse(const vector<string>& _examples);
	int mostFrequentClassValue(const vector<string>& _examples);
	bool edgeCases_CreateTree(const vector<string>& _examples, const vector<Attribute>& _attrList);

};

#endif