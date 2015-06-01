#ifndef STR_IS_NUM_H
#define STR_IS_NUM_H

#include <string>

inline bool strIsNumber(char* buff){
	int isDigitFlag;
	bool isDot;
	bool isNeg;
	int len = strlen(buff);
	char c;

	for(int i = 0; i < len; i++)
	{
		c = *buff++;
		isDigitFlag = isdigit(c);

		(c == '.') ? (isDot = true) : (isDot = false);

		(c == '-') ? (isNeg = true) : (isNeg = false);

		if(!(isDigitFlag || isDot || isNeg))
		{
			return 0;
		}
	}

	return 1;
}

#endif