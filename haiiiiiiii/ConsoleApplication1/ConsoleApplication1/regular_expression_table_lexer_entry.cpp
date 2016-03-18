#include "stdafx.h"

#include "regular_expression_table_lexer_entry.h"

#include <Windows.h>

void swap(regular_expression_table_lexer_entry &left, regular_expression_table_lexer_entry &right)
{
	using std::swap;

	swap(left._expression, right._expression);
}

regular_expression_table_lexer_entry::regular_expression_table_lexer_entry()
{
}

regular_expression_table_lexer_entry::regular_expression_table_lexer_entry(const regular_expression_table_lexer_entry &other) :
	  _expression(other._expression)
{
}

regular_expression_table_lexer_entry::regular_expression_table_lexer_entry(regular_expression_table_lexer_entry &&other) :
	  regular_expression_table_lexer_entry()
{
	swap(*this, other);
}

regular_expression_table_lexer_entry::~regular_expression_table_lexer_entry()
{
}

regular_expression_table_lexer_entry &regular_expression_table_lexer_entry::operator =(regular_expression_table_lexer_entry other)
{
	swap(*this, other);

	return *this;
}

bool regular_expression_table_lexer_entry::lex(std::istream &stream, token &t) const
{
	bool result = false;

	std::smatch match;

	std::istreambuf_iterator<char> start(stream);
	std::istreambuf_iterator<char> end;

	HANDLE handle = ::CreateFile(_T("c:\lol.txt"), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	SECURITY_ATTRIBUTES attributes;

	::CreateFileMapping(handle, &attributes, , 0, 0, );

	if (std::regex_search(stream.beg, stream.end, match, _expression))
	{
		std::cout << "boop" << std::endl;
	}

	if (std::regex_search(start, end, match, _expression))
	{

	}

	return result;
}
