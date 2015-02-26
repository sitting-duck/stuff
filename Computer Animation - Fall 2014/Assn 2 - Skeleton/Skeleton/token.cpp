////////////////////////////////////////
// token.cpp
////////////////////////////////////////

#include "token.h"
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Tokenizer::Tokenizer(const std::string& _filename) : File(0), LineNum(0), filename(_filename) {
	Open(_filename);
}

////////////////////////////////////////////////////////////////////////////////

Tokenizer::~Tokenizer() {
	if(File) {
		std::cout << "ERROR: Tokenizer::~Tokenizer()- Closing file '" << filename << "'" << std::endl;
		fclose((FILE*)File);
	}
}

////////////////////////////////////////////////////////////////////////////////

bool Tokenizer::Open(const std::string& _filename) {
	File = (void*)fopen(_filename.c_str(), "r");
	LineNum=1;
	if(File==0) {
		std::cout << "ERROR: crTokenzier::Open()- Can't open file '" << _filename << "'" << std::endl;
		return false;
	}
	filename, _filename;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Tokenizer::Close() {
	if(File) fclose((FILE*)File);
	else return false;

	File=0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Tokenizer::Abort(char *error) {
	printf("ERROR '%s' line %d: %s\n", filename, LineNum, error);
	Close();
	return false;
}

////////////////////////////////////////////////////////////////////////////////

char Tokenizer::GetChar() {
	char c=char(getc((FILE*)File));
	if(c=='\n') LineNum++;
	return c;
}

////////////////////////////////////////////////////////////////////////////////

char Tokenizer::CheckChar() {
	int c=getc((FILE*)File);
	ungetc(c,(FILE*)File);
	return char(c);
}

////////////////////////////////////////////////////////////////////////////////

int Tokenizer::GetInt() {
	SkipWhitespace();
	int pos=0;
	char temp[256];

	// Get first character ('-' or digit)
	char c=CheckChar();
	if(c=='-') {
		temp[pos++]=GetChar();
		c=CheckChar();
	}
	if(!isdigit(c)) {
		printf("ERROR: Tokenizer::GetInt()- Expecting int on line %d of '%s'\n",LineNum, filename);
		return 0;
	}
	temp[pos++]=GetChar();

	// Get integer potion
	while(isdigit(c=CheckChar())) temp[pos++]=GetChar();

	// Finish
	temp[pos++]='\0';
	return atoi(temp);
}

////////////////////////////////////////////////////////////////////////////////

// BUG: can't parse ".2", "f", or "F"
// Uses: [-]I[.[I]][(e|E)[+|-]I]
// Should use: [+|-](I|I.|.I|I.I)[(e|E)[+|-]I][f|F]

float Tokenizer::GetFloat() {
	SkipWhitespace();
	int pos=0;
	char temp[256];

	// Get first character ('-' or digit)
	char c=CheckChar();
	if(c=='-') {
		temp[pos++]=GetChar();
		c=CheckChar();
	}
	if(!isdigit(c)) {
		std::cout << "ERROR: Tokenizer::GetFloat()- Expecting float on line " << LineNum << " of '" << filename << "' '" << c << "'" << std::endl;
		return 0.0f;
	}
	temp[pos++]=GetChar();

	// Get integer potion of mantissa
	while(isdigit(c=CheckChar())) temp[pos++]=GetChar();

	// Get fraction component
	if(c=='.') {
		temp[pos++]=GetChar();
		while(isdigit(c=CheckChar())) temp[pos++]=GetChar();
	}

	// Get exponent
	if(c=='e' || c=='E') {
		temp[pos++]=GetChar();
		c=CheckChar();
		if(c=='+' || c=='-') {
			temp[pos++]=GetChar();
			c=CheckChar();
		}
		if(!isdigit(c)) {
			std::cout << "ERROR: Tokenizer::GetFloat()- Poorly formatted float exponent on line " << LineNum << " of '" << filename << "'\n" << std::endl;
			return 0.0f;
		}
		while(isdigit(c=CheckChar())) temp[pos++]=GetChar();
	}

	// Finish
	temp[pos++]='\0';
	return float(atof(temp));
}

////////////////////////////////////////////////////////////////////////////////

bool Tokenizer::GetToken(std::string& _buf) {
	SkipWhitespace();

	int pos=0;
	char c=CheckChar();
	while(c!=' ' && c!='\n' && c!='\t' && c!='\v' && c!='\r' && c!='\f' && !feof((FILE*)File)) {
		_buf.append(1, GetChar());
		c=CheckChar();
	}
	return !feof((FILE*)File);
}

////////////////////////////////////////////////////////////////////////////////

bool Tokenizer::FindToken(const char *tok) {
	int pos=0;
	while(tok[pos]!='\0') {
		if(feof((FILE*)File)) return false;
		char c=GetChar();
		if(c==tok[pos]) pos++;
		else pos=0;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Tokenizer::SkipWhitespace() {
	char c=CheckChar();
	bool white=false;
	while(isspace(c)) {
		GetChar();
		c=CheckChar();
		white=true;
	}
	return white;
}

////////////////////////////////////////////////////////////////////////////////

bool Tokenizer::SkipLine() {
	char c=GetChar();
	while(c!='\n') {
		if(feof((FILE*)File)) return false;
		c=GetChar();
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Tokenizer::Reset() {
	if(fseek((FILE*)File,0,SEEK_SET)) return false;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
