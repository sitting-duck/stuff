#ifndef FIXED_ARRAY_H
#define FIXED_ARRAY_H

template <class T = int, long Lower = 0, long Upper = 10>	// Lower and Upper are constants
	class FixedArray
		{
		public:
											FixedArray	();
											FixedArray	(const FixedArray <T, Lower, Upper> &);
			FixedArray <T, Lower, Upper> &	operator =	(const FixedArray <T, Lower, Upper> &);
			FixedArray <T, Lower, Upper> &	GetAt	(const FixedArray <T, Lower, Upper> &);
			FixedArray <T, Lower, Upper> &	operator =	(FixedArray <T, Lower, Upper> &);
			FixedArray <T, Lower, Upper> &	SetAt	(FixedArray <T, Lower, Upper> &);
					T &						operator []	(long);
			const	T &						operator []	(long) const;
		private:
			T	A	[Upper - Lower + 1];
		};

template <class T, long Lower, long Upper>
	FixedArray <T, Lower, Upper>::FixedArray ()
		{
		}

template <class T, long Lower, long Upper>
	FixedArray <T, Lower, Upper>::FixedArray (const FixedArray <T, Lower, Upper> & Arr)
		{
		for (long i = 0; i < (Upper - Lower + 1); i++)
			A [i] = Arr.A [i];
		}

template <class T, long Lower, long Upper>
	FixedArray <T, Lower, Upper> & FixedArray <T, Lower, Upper>::operator = (const FixedArray <T, Lower, Upper> & Arr)
		{
		for (long i = 0; i < (Upper - Lower + 1); i++)
			A [i] = Arr.A [i];
		return *this;
		}

template <class T, long Lower, long Upper>
	FixedArray<T, Lower, Upper> & FixedArray <T, Lower, Upper>::GetAt(const FixedArray <T, Lower, Upper>& Arr)
	{
	for (long i = 0; i < (Upper - Lower + 1); i++)
			A [i] = Arr.A [i];
		return *this;
	}

template <class T, long Lower, long Upper>
	FixedArray <T, Lower, Upper> & FixedArray <T, Lower, Upper>::operator = (FixedArray <T, Lower, Upper> & Arr)
		{
		for (long i = 0; i < (Upper - Lower + 1); i++)
			A [i] = Arr.A [i];
		return *this;
		}

template <class T, long Lower, long Upper>
	FixedArray<T, Lower, Upper> & FixedArray <T, Lower, Upper>::SetAt(FixedArray <T, Lower, Upper>& Arr)
	{
	for (long i = 0; i < (Upper - Lower + 1); i++)
			A [i] = Arr.A [i];
		return *this;
	}

template <class T, long Lower, long Upper>
	T & FixedArray <T, Lower, Upper>::operator [] (long i)
		{
		return A [i - Lower];
		}

template <class T, long Lower, long Upper>
	const T & FixedArray <T, Lower, Upper>::operator [] (long i) const
		{
		return A [i - Lower];
		}

template <class T, long Lower, long Upper>
	void Func2 (FixedArray <T, Lower, Upper> & Arr)
		{
		}

#endif
