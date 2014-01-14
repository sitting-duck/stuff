#ifndef	WCS_POINTER_H
#define	WCS_POINTER_H

#include "RefCount.h"

#ifndef NULL
#define NULL	0
#endif

#ifdef	NULL_POINTER
#undef	NULL_POINTER
#endif
#define	NULL_POINTER	(static_cast <T *> (NULL))

#define Obj(P) (*P)

// NOTE:
//		1) The class used to replace T in the template below must be derived from RefCount
//		2) The object that WCS_Pointer "points to" must be dynamically allocated

template <class T>
	class WCS_Pointer
		{
		public:
			enum	Exceptions		{NullPointerException};

										WCS_Pointer		();
			explicit					WCS_Pointer		(T *);
										WCS_Pointer		(const WCS_Pointer<T> &);
			virtual						~WCS_Pointer	();
					bool				DoesNotExist	() const;
					bool				Exists			() const;
					WCS_Pointer <T> &	New				();
					WCS_Pointer <T> &	New				(const T &);
					T &					ObjectOf		()						throw (...);
			const	T &					ObjectOf		() const				throw (...);
					WCS_Pointer<T> &	PointsTo		(const WCS_Pointer<T> &);
					WCS_Pointer<T> &	SetTo			(const WCS_Pointer<T> &);
					void				SetToNull		();
					T &					operator *		()						throw (...);
			const	T &					operator *		() const				throw (...);
					T*					operator ->		()						throw (...);
			const	T*					operator ->		() const				throw (...);
					WCS_Pointer<T> &	operator =		(const WCS_Pointer<T> &);
					bool				operator ==		(const WCS_Pointer<T> &) const;
					bool				operator !		() const;
					bool				operator !=		(const WCS_Pointer<T> &) const;
										operator bool	() const;
		private:
					WCS_Pointer<T> &	Copy			(const WCS_Pointer<T> &);
					void				Decrement		();
					void				SetAndIncrement	(const T *);
					WCS_Pointer<T> &	SetTo			(const T *);
					WCS_Pointer<T> &	operator =		(const T *);

					T *					Ptr;
		};

template <class T>
	WCS_Pointer <T>::WCS_Pointer ():Ptr (NULL_POINTER)
		{
		}

template <class T>
	WCS_Pointer <T>::WCS_Pointer (T * p)
		{
		SetAndIncrement (p);
		}

template <class T>
	WCS_Pointer <T>::WCS_Pointer (const WCS_Pointer<T> & P)
		{
		SetAndIncrement (P.Ptr);
		}

template <class T>
	WCS_Pointer <T>::~WCS_Pointer ()
		{
		Decrement ();
		}

template <class T>
	inline bool WCS_Pointer<T>::DoesNotExist () const
		{
		return Ptr == NULL_POINTER;
		}

template <class T>
	inline bool WCS_Pointer<T>::Exists () const
		{
		return Ptr != NULL_POINTER;
		}

template <class T>
	inline WCS_Pointer <T> & WCS_Pointer<T>::New ()
		{
		Decrement ();
		SetAndIncrement (new T);
		return *this;
		}

template <class T>
	inline WCS_Pointer <T> & WCS_Pointer<T>::New (const T & t)
		{
		Decrement ();
		SetAndIncrement (new T (t));
		return *this;
		}

template <class T>
	inline T & WCS_Pointer<T>::ObjectOf ()
		{
		if (Ptr)
				return *Ptr;
			else
				throw NullPointerException;
		}

template <class T>
	inline const T & WCS_Pointer<T>::ObjectOf () const
		{
		if (Ptr)
				return *Ptr;
			else
				throw NullPointerException;
		}

template <class T>
	inline WCS_Pointer<T> & WCS_Pointer<T>::PointsTo (const WCS_Pointer<T> & P)
		{
		return Copy (P);
		}

template <class T>
	inline WCS_Pointer<T> & WCS_Pointer<T>::SetTo (const WCS_Pointer<T> & P)
		{
		return SetTo (P.Ptr);
		}

template <class T>
	inline void WCS_Pointer<T>::SetToNull ()
		{
		SetTo (NULL_POINTER);
		}

template <class T>
	inline T & WCS_Pointer<T>::operator * ()
		{
		return ObjectOf ();
		}

template <class T>
	inline const T & WCS_Pointer<T>::operator * () const
		{
		return ObjectOf ();
		}

template <class T>
	inline T * WCS_Pointer<T>::operator -> ()
		{
		if (Ptr)
				return Ptr;
			else
				throw NullPointerException;
		}

template <class T>
	inline const T * WCS_Pointer<T>::operator -> () const
		{
		if (Ptr)
				return Ptr;
			else
				throw NullPointerException;
		}

template <class T>
	inline WCS_Pointer<T> & WCS_Pointer<T>::operator = (const WCS_Pointer<T> & P)
		{
		if (this != &P)
				SetTo (P.Ptr);
			else;
		return *this;
		}

template <class T>
	inline bool WCS_Pointer<T>::operator == (const WCS_Pointer<T> & P) const
		{
		return Ptr == P.Ptr;
		}

template <class T>
	inline bool WCS_Pointer<T>::operator ! () const
		{
		return DoesNotExist ();
		}

template <class T>
	inline bool WCS_Pointer<T>::operator != (const WCS_Pointer<T> & P) const
		{
		return Ptr != P.Ptr;
		}

template <class T>
	inline WCS_Pointer<T>::operator bool () const
		{
		return Exists ();
		}

template <class T>
	inline WCS_Pointer<T> & WCS_Pointer<T>::Copy (const WCS_Pointer<T> & P)
		{
		return *this = P;
		}

template <class T>
	inline void WCS_Pointer<T>::Decrement ()
		{
		if (Ptr)
				(*Ptr).DownCount ();
			else;
		}

template <class T>
	inline void WCS_Pointer<T>::SetAndIncrement (const T * p)
		{
		if ((Ptr = (T *) (p)) != NULL_POINTER)
				(*Ptr).UpCount ();
			else;
		}

template <class T>
	inline WCS_Pointer<T> & WCS_Pointer<T>::SetTo (const T * p)
		{
		Decrement ();
		SetAndIncrement (p);
		return *this;
		}

template <class T>
	inline WCS_Pointer<T> & WCS_Pointer<T>::operator = (const T * p)
		{
		return SetTo (p);
		}

#endif
