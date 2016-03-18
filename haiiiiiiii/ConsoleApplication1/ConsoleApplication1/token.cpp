#include "stdafx.h"

#include "token.h"

void swap(token &left, token &right)
{
	using std::swap;

	swap(left._line, right._line);
	swap(left._position, right._position);
	swap(left._type, right._type);
	swap(left._value, right._value);
}

token::token() :
	  _line(0)
	, _position(0)
{
}

token::token(const std::int32_t line, const std::int32_t position, const std::string &type, const std::string &value) :
	  _line(line)
	, _position(position)
	, _type(type)
	, _value(value)
{
}

token::token(const token &other) :
	  _line(other._line)
	, _position(other._position)
	, _type(other._type)
	, _value(other._value)
{
}

token::token(token &&other) :
	  token()
{
	swap(*this, other);
}

token::~token()
{
}

token &token::operator =(token other)
{
	swap(*this, other);

	return *this;
}
