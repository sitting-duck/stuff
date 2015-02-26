#include "Tokenizer.h"

Tokenizer::Tokenizer(){}

Tokenizer::Tokenizer(const Tokenizer& t){

}

Tokenizer& Tokenizer::operator=(const Tokenizer& t){
	return *this;
}

bool Tokenizer::OpenFile(const std::string& _filename) {
	File = (void*)fopen(_filename.c_str(), "r");
	if(File == 0) {
		std::cout << "ERROR: SkelFactory::OpenFile()- Can't open file '" << _filename << "'" << std::endl;
		return false;
	}
	filename = _filename;
	return true;
}

bool Tokenizer::openFile(const std::string& _filename) {
	fileStream.open(_filename);
	return true;
}

bool Tokenizer::Close() {
	if(File) fclose((FILE*)File);
	else return false;
	
	File = 0;
	return true;
}

bool Tokenizer::close() {
	fileStream.close();
	return true;
}

bool Tokenizer::SkipWhiteSpace(){
	char c = CheckChar();
	bool white = false;
	while(isspace(c)) {
		GetChar();
		c = CheckChar();
		white = true;
	}
	return white;
}

bool Tokenizer::GetToken(std::string& _buf){
	SkipWhiteSpace();

	int pos = 0;
	char c = CheckChar();
	while(c != ' ' && c != '\n' && c != '\t' && c != '\v' && c != '\r' && c != '\f' && !feof((FILE*)File)) {
		_buf.append(1, GetChar());
		c = CheckChar();
	}
	return !feof((FILE*)File);
}

char Tokenizer::CheckChar(){
	int c = getc((FILE*)File);
	ungetc(c, (FILE*)File);
	return char(c);
}

char Tokenizer::GetChar() {
	char c = char(getc((FILE*)File));
	if(c == '\n')
		return c;
}

void Tokenizer::putFileInBuffer(){
	fileStream.seekg(0, std::ios::end);
	int length = fileStream.tellg();
	fileStream.seekg(0, std::ios::beg);
	//fileBuffer = new char[length + 1];
	fileBuffer = (char*)calloc(length + 1, sizeof(char));
	fileBuffer[length] = '\0';
	fileStream.read(fileBuffer, length);
}

std::vector<std::string> Tokenizer::tokenize(){
	char* pch;
	char tempBuf[100] = {'\0'};
	std::string strToken;

	pch = strtok(fileBuffer, "\t\n \0\r");
	strcpy(tempBuf, pch);
	strToken.assign(tempBuf);
	memset(tempBuf, 0, 100);
	tokens.push_back(strToken);
	strToken.clear();
	do{
		pch = strtok(NULL, "\t\n \0\r");
		if(pch == NULL){ break; }
		strcpy(tempBuf, pch);
		strToken.assign(tempBuf);
		memset(tempBuf, 0, 100);
		tokens.push_back(strToken);
		strToken.clear();
	} while(pch != NULL);
	return tokens;
}