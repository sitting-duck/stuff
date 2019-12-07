#ifndef UBSTACK_H
#define UBSTACK_H

template <class DATA>
	class UBStack: private UBArray <DATA, unsigned long>
		{
		public:
					UBStack		();
					~UBStack	();
			bool	Pop			(DATA &);
			bool	Push		(const DATA &);
		private:
					UBStack		(const UBStack <DATA> &);
			void	operator =	(const UBStack <DATA> &);

					unsigned long	Top;
		};

template <class DATA>
	UBStack <DATA>::UBStack (): Top (0)
		{
		}

template <class DATA>
	UBStack <DATA>::~UBStack ()
		{
		}

template <class DATA>
	bool UBStack <DATA>::Pop (DATA & D)
		{
		if (Top > 0)
				{
				D = (*this) [--Top];
				return true;
				}
			else
				return false;
		}

template <class DATA>
	bool UBStack <DATA>::Push (const DATA & D)
		{
		(*this) [Top++] = D;
		return true;
		}

#endif
