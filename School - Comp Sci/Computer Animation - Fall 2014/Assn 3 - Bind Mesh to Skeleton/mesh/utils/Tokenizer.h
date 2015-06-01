#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

class SkelFactory;
class MeshFactory;

class Tokenizer{
	friend SkelFactory;
	friend MeshFactory;

private:
	std::string filename;

	void *File;

	std::ifstream fileStream;

	char* fileBuffer;

	std::vector<std::string> tokens;

	Tokenizer(const Tokenizer& t);


	Tokenizer& operator=(const Tokenizer& t);
public:
	Tokenizer();

	

	bool OpenFile(const std::string& _filename);

	bool openFile(const std::string& _filename);

	bool Close();

	bool close();

	bool SkipWhiteSpace();

	bool GetToken(std::string& _buf);

	char CheckChar();

	char GetChar();

	void putFileInBuffer();

	std::vector<std::string> tokenize();
};

#endif