#ifndef TOKEN_STRATEGY_H
#define TOKEN_STRATEGY_H

#define _REGEX(x)		#x

class TokenStrategy{

public:
	TokenStrategy();
	~TokenStrategy();

private:

	const static char number_regex[];

	const static char var_name_regex[];

	const static char balljointTypeName[];


};

#endif