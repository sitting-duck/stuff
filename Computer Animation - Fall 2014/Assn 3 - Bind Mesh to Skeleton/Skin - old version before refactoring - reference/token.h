////////////////////////////////////////
// token.h
////////////////////////////////////////

#ifndef CSE169_TOKEN_H
#define CSE169_TOKEN_H

#include<string>
#include "core.h"

////////////////////////////////////////////////////////////////////////////////

class Tokenizer {
public:
	Tokenizer(const std::string& _filename);
	~Tokenizer();

	bool Open(const std::string& _filename);
	bool Close();

	bool Abort(char *error);	// Prints error & closes file, and always returns false

	// Tokenization
	char GetChar();
	char CheckChar();
	int GetInt();
	float GetFloat();
	bool GetToken(std::string& _buf);
	bool FindToken(const char *tok);
	bool SkipWhitespace();
	bool SkipLine();
	bool Reset();

	// Access functions
	const std::string& GetFileName() const { return filename; }
	int GetLineNum() const {return LineNum;}

private:
	void *File;
	std::string filename;
	int LineNum;
};

////////////////////////////////////////////////////////////////////////////////

/*
The Tokenizer class for reading simple ascii data files. The GetToken function
just grabs tokens separated by whitespace, but the GetInt and GetFloat functions
specifically parse integers and floating point numbers. SkipLine will skip to
the next carraige return. FindToken searches for a specific token and returns
true if it found it.
*/

#endif
