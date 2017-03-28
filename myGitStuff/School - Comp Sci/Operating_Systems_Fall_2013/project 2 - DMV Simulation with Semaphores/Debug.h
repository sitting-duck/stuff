#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

typedef unsigned int uint;
using namespace std;

class Debug
{
public: 
	struct color_code
	{
		const char* tag;
		const char* code;
		const char* name;
	};
	
private: 
	uint indent_level; 	//how many tabs will printed before message
	uint indent_size; 	//how many spaces per indent
	bool color_on;
	static const uint num_colors = 9;
	static const color_code colors[num_colors]; //holds the color_code structs (colors we can print) 

public:
	Debug(uint _indent_size = 1, bool _color_on = true);

	~Debug();

	Debug* log(const char* _msg_to_print, ...);
	
	Debug* log(string& _msg_to_print, ...);

	string get_indent_string();

	string colorize(const string& _string);

	Debug* indent(const int _how_many_to_indent);

	Debug* reset_indent();

	Debug* set_indent_size(const uint _new_indent_size);
};

inline Debug* Debug::indent(const int _how_many_to_indent)
{
	this->indent_level += _how_many_to_indent;
	if(this->indent_level < 0)
	{
		indent_level = 0;
	}
	return this;
}

inline Debug* Debug::reset_indent()
{
	this->indent_level = 0;
	return this;
}

inline Debug* Debug::set_indent_size(const uint _new_indent_size)
{
	this->indent_size = _new_indent_size;
	return this;
}

#endif
