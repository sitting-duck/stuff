#include <fstream>
#include <iostream>
#include "UBArray.h"

typedef unsigned int ULONG;
using namespace std;

class File
{
private:
	struct RecordInfo
	{
		ULONG Length;
		ULONG Offset;

		RecordInfo():Length(0), Offset(0){}
	};

public:
	enum ErrorCode {OK};

	File();
	~File();
	ErrorCode Write();

private:
			File		(const File &);
		void	operator =	(const File &);

		fstream						MyFile;
		ULONG						NumRecords;
		ULONG						EndOfData;
		UBArray <RecordInfo, ULONG>	RecInfo;

};

File::File()
{

}

File::~File()
{

}

File::ErrorCode File::Write()
	{
		MyFile.seekp(EndOfData);
		MyFile.write("poop", 4);
		return OK;

	}