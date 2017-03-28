#pragma once

#include <cstdint>
#include <string>

class token
{
public:
	token();
	token(const std::int32_t line, const std::int32_t position, const std::string &type, const std::string &value);
	token(const token &other);
	token(token &&other);
	virtual ~token();

	token &operator =(token other);

	friend void swap(token &left, token &right);

private:
	std::int32_t _line;
	std::int32_t _position;
	std::string _type;
	std::string _value;
};

void swap(token &left, token &right);
