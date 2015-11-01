#ifndef ARRAY_H
#define ARRAY_H

template <class T>
	class Array
		{
		public:
					Array		();
					Array		(const Array <T> &);
					Array		(long);
					Array		(int);
					~Array		();
			T &		operator =	(const Array <T> &);
			void	Test		();
		private:
			T	* pArray;
			long	NumElements;
		};

template <class T>
	Array <T>::Array ()
		{
		pArray = new T [10];
		}

template <class T>
	Array <T>::~Array ()
		{
		delete [] pArray;
		}

template <class T>
	Array <T>::Array (const Array <T> & A)
		{
		pArray = new T [10];
		for (int i = 0; i < 10; i++)
			pArray [i] = A.pArray [i];
		}

template <class T>
	void Array <T>::Test ()
		{
		dfv fmf f	// template methods are not compiled unless they are called
		}

#endif
