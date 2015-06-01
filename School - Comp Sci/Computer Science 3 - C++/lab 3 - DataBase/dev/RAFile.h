#ifndef RAFILE_H
#define RAFILE_H

#include <fstream>

using namespace std;

#include "UBArray.h"
#include "WCS_String.h"

class RAFile
	{
	public:
		typedef unsigned long ULONG;

		enum	ErrorCode	{OK, FileAlreadyOpen, CannotOpenFile, IndexInvalid};
	private:
		struct RecordInfo
			{
			ULONG	Offset;
			ULONG	Length;

			RecordInfo():Offset(), Length(0){}
			};
			

	public:
					RAFile	();
					~RAFile	();
		bool		IsOpen	() const;
		ErrorCode	Open	(const WCS_String &);
		void		Close	();
		ErrorCode	Read	(ULONG, WCS_String &);
		ErrorCode	Replace	(ULONG, const WCS_String &);
		ErrorCode	Insert	(ULONG, const WCS_String &);
		ErrorCode	Delete	(ULONG);
	private:
				RAFile		(const RAFile &);
		void	operator =	(const RAFile &);

		fstream						MyFile;
		ULONG						NumRecords;
		ULONG						EndOfData;
		UBArray <RecordInfo, ULONG>	RecInfo;
	};

inline bool RAFile::IsOpen () const
	{
	return MyFile.is_open ();
	}

#endif
