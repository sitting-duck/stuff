#include "RAFile.h"

RAFile::RAFile (): NumRecords (0)
	{
		
	}

RAFile::~RAFile ()
	{
	if (MyFile.is_open ())
			Close ();
		else;
	}

void RAFile::Close ()
	{
	// write any unwritten info back to the file (RecInfo, NumRecords
	MyFile.close ();
	}

RAFile::ErrorCode RAFile::Open (const WCS_String & Str)
	{
	if (!MyFile.is_open ())
			{
			MyFile.open ((const char *) Str, ios_base::in | ios_base::out | ios_base::binary);
			if (!MyFile.is_open ())
					{
					MyFile.clear ();
					MyFile.open ((const char *) Str, ios_base::out | ios_base::binary);
					if (!MyFile.is_open ())
							return CannotOpenFile;
						else
							{
							NumRecords = 0;
							MyFile.write ((const char *) &NumRecords, sizeof (NumRecords));
							MyFile.close ();
							MyFile.open ((const char *) Str, ios_base::in | ios_base::out | ios_base::binary);
							if (!MyFile.is_open ())
									return CannotOpenFile;
								else;
							}
					}
				else;
			MyFile.read ((char *) &NumRecords, sizeof (NumRecords));
			if (NumRecords > 0)
					{
					MyFile.seekg (-(static_cast<long> (NumRecords * sizeof (RecordInfo))), ios_base::end);
					EndOfData = MyFile.tellg ();
					for (ULONG i = 0; i < NumRecords; i++)
						MyFile.read ((char *) &RecInfo [i], sizeof (RecordInfo));
					}
				else;
			}
		else
			return FileAlreadyOpen;
	}

RAFile::ErrorCode RAFile::Read (ULONG Index, WCS_String & Data)
	{
	if (Index < NumRecords)
			if (RecInfo [Index].Length == 0)
					{
					Data = "";
					return OK;
					}
				else
					{
					char * pChar;

					MyFile.seekg (RecInfo [Index].Offset);
					pChar = new char [RecInfo [Index].Length + 1];
					MyFile.read (pChar, RecInfo [Index].Length);
					pChar [RecInfo [Index].Length] = '\0';
					Data = pChar;
					delete [] pChar;
					return OK;
					}
		else
			return IndexInvalid;
	}

RAFile::ErrorCode RAFile::Replace (ULONG Index, const WCS_String & Data)
	{
	if (Index < NumRecords)
			{
			if (Data.Length () <= RecInfo [Index].Length)
					MyFile.seekp (RecInfo [Index].Offset);
					//MyFile.seekp (RecInfo [Index].Offset, ios::beg);
				else
					{
					MyFile.seekp (EndOfData);
					RecInfo [Index].Offset = EndOfData;
					EndOfData = MyFile.tellp ();
					}
			MyFile.write ((const char *) Data, Data.Length ());
			RecInfo [Index].Length = Data.Length ();
			return OK;
			}
		else
			return IndexInvalid;
	}

RAFile::ErrorCode	RAFile::Insert	(ULONG Index, const WCS_String & Data)
{
	
	if (Index <= NumRecords)//we're gonna do a bunch of crap to shift over all the indices
	{	
		const char* pch;
		pch = Data;

		WCS_String temp("");
		MyFile.seekp(RecInfo[Index].Offset);
		MyFile.read(temp.GetPtr(), (EndOfData - RecInfo[Index].Offset));

		MyFile.seekp(RecInfo[Index].Offset);
		MyFile.write(pch, Data.Length());
		MyFile.seekp(RecInfo[Index].Offset + Data.Length());
		MyFile.write(temp.GetPtr(), temp.Length());
		

		for(int i = Index; i < NumRecords; i++)
		{
			RecInfo[Index + 1].Offset = RecInfo[Index].Offset;
			RecInfo[Index + 1].Length = RecInfo[Index].Length;
		}
		//Replace(Index, Data);
		NumRecords++;
		return OK;
	}
	else
	{
		for(int i = NumRecords; i < Index; i++)
		{
			RecInfo[i].Length = 0;
			RecInfo[i].Offset = RecInfo[i-1].Offset;
		}
				const char* pch;
		pch = Data;

		WCS_String temp("");


		MyFile.seekp(RecInfo[Index].Offset);
		MyFile.read(temp.GetPtr(), (EndOfData - RecInfo[Index].Offset));

		MyFile.seekp(RecInfo[Index].Offset);
		MyFile.write(pch, Data.Length());
		MyFile.seekp(RecInfo[Index].Offset + Data.Length());
		MyFile.write(temp.GetPtr(), temp.Length());
		
		RecInfo[Index].Offset = Index;
		RecInfo[Index].Length = Data.Length();
		NumRecords++;
		return OK;
	}
}