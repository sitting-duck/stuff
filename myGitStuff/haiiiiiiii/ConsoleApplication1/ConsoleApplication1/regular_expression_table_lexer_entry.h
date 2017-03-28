#pragma once

#include <iostream>
#include <regex>

class token;

class regular_expression_table_lexer_entry
{
public:
	regular_expression_table_lexer_entry();
	regular_expression_table_lexer_entry(const regular_expression_table_lexer_entry &other);
	regular_expression_table_lexer_entry(regular_expression_table_lexer_entry &&other);
	virtual ~regular_expression_table_lexer_entry();

	regular_expression_table_lexer_entry &operator =(regular_expression_table_lexer_entry other);

	friend void swap(regular_expression_table_lexer_entry &left, regular_expression_table_lexer_entry &right);

	bool lex(std::istream &stream, token &t) const;

private:
	std::regex _expression;
};

void swap(regular_expression_table_lexer_entry &left, regular_expression_table_lexer_entry &right);
