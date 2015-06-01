#include <conio.h>
#include <ctype.h>	// could use <cctype>
#include <math.h>	// could use <cmath>

#include "ReadFunctions.h"

static void BackSpace ()	// static means this function can only be used by other functions in this file
	{
	_putch ('\b');
	_putch (' ');
	}

double ReadDouble ()
	{
	char	c;
	bool	Digits		(false);
	int		Fraction	(0);
	double	Num			(0.0);
	int		Sign		(0);

	while (!isspace (c = static_cast <char> (_getch ())))
		{
		switch (c)
			{
			case '+':
			case '-':
				if ((Sign == 0) && !Digits)
						if (c == '+')
								Sign = 1;
							else  // c == '-'
								Sign = -1;
					else
						c = '\a';
				break;
			case '.':
				if (Fraction == 0)
						Fraction = 1;
					else
						c = '\a';
				break;
			case '\b':
				if (Fraction > 0)
						{
						BackSpace ();
						Fraction /= 10;
						if (Fraction > 0)
								{
								Num = static_cast <int> (Num * Fraction);
								Num /= Fraction;
								}
							else;
						}
					else
						if (Digits)
								{
								BackSpace ();
								Num = static_cast <int> (Num) / 10;
								if (Num == 0.0)
										Digits = false;
									else;
								}
							else
								if (Sign != 0)
										{
										BackSpace ();
										Sign = 0;
										}
									else
										c = '\a';
				break;
			case '0':
				if (!Digits && (Fraction == 0))	// doesn't do leading zeros
						{
						c = '\a';
						break;
						}
					else;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				Digits = true;
				if (Fraction > 0)
						{
						Fraction *= 10;
						Num = Num + ((c - '0') / static_cast <double> (Fraction));
						}
					else
						Num = (Num * 10.0) + (c - '0');
				break;
			default:
				c = '\a';
			}
		_putch (c);
		}
	if (c == '\r')
			c = '\n';
		else;
	_putch (c);
	if (Sign < 0)
			Num = -Num;
		else;
	return Num;
	}

int ReadInteger ()
	{
	char	c;
	bool	Digits	(false);
	int		Num		(0);
	int		Sign	(0);

	while (!isspace (c = static_cast <char> (_getch ())))
		{
		switch (c)
			{
			case '+':
			case '-':
				if ((Sign == 0) && !Digits)
						if (c == '+')
								Sign = 1;
							else  // c == '-'
								Sign = -1;
					else
						c = '\a';
				break;
			case '\b':
				if (Digits)
						{
						BackSpace ();
						Num /= 10;
						if (Num == 0)
								Digits = false;
							else;
						}
					else
						if (Sign != 0)
								{
								BackSpace ();
								Sign = 0;
								}
							else
								c = '\a';
				break;
			case '0':
				if (!Digits)
						{
						c = '\a';
						break;
						}
					else;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				Digits = true;
				Num = (Num * 10) + (c - '0');
				break;
			default:
				c = '\a';
			}
		_putch (c);
		}
	if (c == '\r')
			c = '\n';
		else;
	_putch (c);
	if (Sign < 0)
			Num = -Num;
		else;
	return Num;
	}

UINT ReadHex ()
	{
	char	c;
	bool	Digits	(false);
	UINT	Num		(0);

	while (!isspace (c = static_cast <char> (_getch ())))
		{
		switch (c)
			{
			case '\b':
				if (Digits)
						{
						BackSpace ();
						Num /= 16;
						if (Num == 0)
								Digits = false;
							else;
						}
					else
						c = '\a';
				break;
			case '0':
				if (!Digits)
						{
						c = '\a';
						break;
						}
					else;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				Digits = true;
				Num = (Num * 16) + (c - '0');
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				Digits = true;
				Num = (Num * 16) + (c - 'a') + 10;
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				Digits = true;
				Num = (Num * 16) + (c - 'A') + 10;
				break;
			default:
				c = '\a';
			}
		_putch (c);
		}
	if (c == '\r')
			c = '\n';
		else;
	_putch (c);
	return Num;
	}
