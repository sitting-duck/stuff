#include "stdafx.h"

#include <cstdint>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include "regular_expression_table_lexer_entry.h"
#include "token.h"

std::int32_t main()
{
	regular_expression_table_lexer_entry entry;

	std::ifstream file(_T("c:\file.txt"));

	if (file)
	{
		token t;

		if (entry.lex(file, t))
		{
			std::cout << _T("LOL") << std::endl;
		}
	}

	return EXIT_SUCCESS;
}
