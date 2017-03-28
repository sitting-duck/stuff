//******************************************************************************
//
//		Example Class to act as a string of characters
//
//		Copyright:	2002-2007  WCS Software Services
//		Author:		Bill Slater
//
//******************************************************************************

#ifndef WCS_STRING_H
#define WCS_STRING_H

#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

#pragma warning (disable:4996)

class WCS_String
	{
//************* Exceptions *****
	public:
		enum		Exceptions	{IndexOutOfBounds};
//************* Method Prototypes *****
	public:
		explicit				WCS_String				(const char * = "")				throw (...);
								WCS_String				(const WCS_String &)			throw (...);
		virtual					~WCS_String				()								throw ();
				int				Compare					(const WCS_String &)	const	throw ();
				int				Compare					(const char *)			const	throw ();
				WCS_String &	Concat					(const WCS_String &)			throw (...);
				WCS_String &	Concat					(const char *)					throw (...);
				WCS_String &	Copy					(const WCS_String &)			throw (...);
				WCS_String &	Copy					(const char *)					throw (...);
				ostream &		Display					(ostream & = cout)		const;
				bool			GetAt					(char &, int)			const	throw (...);
				bool			IsEmpty					()						const	throw ();
				size_t			Length					()						const	throw ();
				istream &		Read					(istream & = cin)				throw (...);
		static	char			ReadChar				(istream & = cin)				throw ();
				bool			SetAt					(char, int)						throw (...);
				WCS_String &	ToLower					()								throw ();
				WCS_String &	ToUpper					()								throw ();
								operator bool			()						const	throw ();
								operator const char *	()						const	throw ();
				WCS_String &	operator =				(const WCS_String &)			throw (...);
				WCS_String &	operator =				(const char *)					throw (...);
				bool			operator <				(const WCS_String &)	const	throw ();
				bool			operator <				(const char *)			const	throw ();
				bool			operator <=				(const WCS_String &)	const	throw ();
				bool			operator <=				(const char *)			const	throw ();
				bool			operator ==				(const WCS_String &)	const	throw ();
				bool			operator ==				(const char *)			const	throw ();
				bool			operator >=				(const WCS_String &)	const	throw ();
				bool			operator >=				(const char *)			const	throw ();
				bool			operator >				(const WCS_String &)	const	throw ();
				bool			operator >				(const char *)			const	throw ();
				bool			operator !=				(const WCS_String &)	const	throw ();
				bool			operator !=				(const char *)			const	throw ();
				WCS_String		operator &				(const WCS_String &)	const	throw (...);
				WCS_String		operator &				(const char *)			const	throw (...);
				WCS_String &	operator &=				(const WCS_String &)			throw (...);
				WCS_String &	operator &=				(const char *)					throw (...);
				char &			operator []				(int)							throw (...);
				char			operator []				(int)					const	throw (...);

				char* getPtr();
	private:
				bool			IsValidSubscript		(int)					const	throw ();
				void			LocalCheckAndCopy		(const char *)					throw (...);
				WCS_String &	LocalConcat				(const char *)					throw (...);
				void			LocalCopy				(const char *)					throw (...);
				WCS_String		NewConcat				(const char *)			const	throw (...);
								operator char *			()						const	throw ();
//************* Properties *****
	private:
				char *	pChar;
				size_t	CharCount;
				size_t	MaxSize;
	};

//************* Method Definitions *****

inline WCS_String::WCS_String (const char * p): CharCount (0), MaxSize (0), pChar (0)
	{
	LocalCopy (p);
	}

inline WCS_String::WCS_String (const WCS_String & M)
	{
	LocalCopy (M.pChar);
	}

inline int WCS_String::Compare (const WCS_String & M) const
	{
	return strcmp (pChar, M.pChar);
	}

inline int WCS_String::Compare (const char * p) const
	{
	return strcmp (pChar, p);
	}

inline WCS_String & WCS_String::Concat (const WCS_String & M)
	{
	return LocalConcat (M.pChar);
	}

inline WCS_String & WCS_String::Concat (const char * p)
	{
	return LocalConcat (p);
	}

inline WCS_String & WCS_String::Copy (const WCS_String & M)
	{
	return *this = M;
	}

inline WCS_String & WCS_String::Copy (const char * p)
	{
	return *this = p;
	}

inline ostream & WCS_String::Display (ostream & out) const
	{
	return out << pChar;
	}

inline bool WCS_String::GetAt (char & c, int i) const
	{
	if (IsValidSubscript (i))
			{
			c = pChar [i];
			return true;
			}
		else
			return false;
	}

inline bool WCS_String::IsEmpty () const
	{
	return Length () == 0;
	}

inline bool WCS_String::IsValidSubscript (int i) const
	{
	return (i >= 0) && (i < static_cast <int> (CharCount));
	}

inline size_t WCS_String::Length () const
	{
	return CharCount;
	}

inline WCS_String WCS_String::NewConcat (const char * p) const
	{
	WCS_String S (*this);
	S.Concat (p);
	return S;
	}

inline WCS_String::operator bool () const
	{
	return Length () > 0;
	}

inline WCS_String::operator const char * () const
	{
	return pChar;
	}

inline WCS_String & WCS_String::operator = (const WCS_String & M)
	{
	if (this != &M)
			LocalCheckAndCopy (M.pChar);
		else;
	return *this;
	}

inline WCS_String & WCS_String::operator = (const char * p)
	{
	LocalCheckAndCopy (p);
	return *this;
	}

inline bool WCS_String::operator <	(const WCS_String & M) const
	{
	return Compare (M) < 0;
	}

inline bool WCS_String::operator <	(const char * p) const
	{
	return Compare (p) < 0;
	}

inline bool operator <	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) > 0;
	}

inline bool WCS_String::operator <=	(const WCS_String & M) const
	{
	return Compare (M) <= 0;
	}

inline bool WCS_String::operator <=	(const char * p) const
	{
	return Compare (p) <= 0;
	}

inline bool operator <=	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) >= 0;
	}

inline bool WCS_String::operator ==	(const WCS_String & M) const
	{
	return Compare (M) == 0;
	}

inline bool WCS_String::operator ==	(const char * p) const
	{
	return Compare (p) == 0;
	}

inline bool operator ==	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) == 0;
	}

inline bool WCS_String::operator >=	(const WCS_String & M) const
	{
	return Compare (M) >= 0;
	}

inline bool WCS_String::operator >=	(const char * p) const
	{
	return Compare (p) >= 0;
	}

inline bool operator >=	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) <= 0;
	}

inline bool WCS_String::operator >	(const WCS_String & M) const
	{
	return Compare (M) > 0;
	}

inline bool WCS_String::operator >	(const char * p) const
	{
	return Compare (p) > 0;
	}

inline bool operator >	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) < 0;
	}

inline bool WCS_String::operator !=	(const WCS_String & M) const
	{
	return Compare (M) != 0;
	}

inline bool WCS_String::operator !=	(const char * p) const
	{
	return Compare (p) != 0;
	}

inline bool operator !=	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) != 0;
	}

inline WCS_String WCS_String::operator & (const WCS_String & M) const
	{
	return NewConcat (M.pChar);
	}

inline WCS_String WCS_String::operator & (const char * p) const
	{
	return NewConcat (p);
	}

inline WCS_String operator & (const char * p, const WCS_String & S)
	{
	WCS_String Temp (p);
	return Temp.Concat (S);
	}

inline WCS_String &	WCS_String::operator &=	(const WCS_String & M)
	{
	return Concat (M);
	}

inline WCS_String &	WCS_String::operator &=	(const char * p)
	{
	return Concat (p);
	}

inline char & WCS_String::operator [] (int i)
	{
	if (IsValidSubscript (i))
			return pChar [i];
		else
			throw IndexOutOfBounds;
	}

inline char WCS_String::operator [] (int i) const
	{
	return (*const_cast <WCS_String *> (this)).operator [] (i);
	}

inline bool WCS_String::SetAt (char c, int i)
	{
	if ((i >= 0) && (i < static_cast <int> (CharCount)))
			{
			pChar [i] = c;
			return true;
			}
		else
			return false;
	}

inline ostream & operator << (ostream & out, const WCS_String & M)
	{
	return M.Display (out);
	}

inline istream & operator >> (istream & in, WCS_String & M)
	{
	return M.Read (in);
	}

inline char* WCS_String::getPtr()
{
	return pChar;
}

#pragma warning (default:4996)

#endif
