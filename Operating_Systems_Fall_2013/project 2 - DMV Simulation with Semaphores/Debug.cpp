#include "Debug.h"
#include <cstdarg>

using namespace std;

const Debug::color_code Debug::colors[Debug::num_colors] = 
{
	{"[.]", "\033[30m", "grey"},
	{"[r]", "\033[31m", "red"},
	{"[g]", "\033[32m", "green"},
	{"[y]", "\033[33m", "yellow"},
	{"[b]", "\033[34m", "blue"},
	{"[m]", "\033[35m", "magenta"},
	{"[c]", "\033[36m", "cyan"},
	{"[w]", "\033[37m", "white"},
	{"[/]", "\033[0m", "end color"}
};

Debug::Debug(uint _indent_size, bool _color_on): indent_level(0), indent_size(_indent_size), color_on(_color_on)
{
	
}

Debug::~Debug()
{
}

Debug* Debug::log(const char* _msg_to_print, ...)
{
	string indent_string = get_indent_string();  //will return a string wi appropriate number of tabs
	printf(indent_string.c_str());

	va_list arguments;   //the fetch the extra arguments, (note the ... in the function header)
	va_start(arguments, _msg_to_print);
	if(this->color_on)
	{
		string msg_to_print(_msg_to_print);
		msg_to_print = colorize(msg_to_print);  
		vprintf(msg_to_print.c_str(), arguments);
	}
	else
	{
		vprintf(_msg_to_print, arguments);
	}
	va_end(arguments);
	printf("%s", this->colors[num_colors - 1].code);
	return this;
}


//TODO: figure out a way to overload this without having to repeat code
Debug* Debug::log(string& _msg_to_print, ...)
{
	va_list arguments;
	va_start(arguments, _msg_to_print);
	if(this->color_on)
	{
		_msg_to_print = colorize(_msg_to_print);
		vprintf(_msg_to_print.c_str(), arguments);
	}
	va_end(arguments);
	printf("%s", colors[num_colors - 1].code);
	return this;
}

string Debug::get_indent_string()
{
	int how_many_spaces = indent_level * indent_size;
	char* indent_string_buffer = (char*)calloc(how_many_spaces + 1, sizeof(char));
	memset(indent_string_buffer, ' ', how_many_spaces * sizeof(char));

	string indent_string = indent_string_buffer;

	return indent_string;
}

string Debug::colorize(const string& _string)
{
	string string_to_color = _string;
	for(uint i = 0; i < this->num_colors; i++)
	{
		int tag_length = strlen(this->colors[i].tag);
		int position = -1;
		do
		{
			position = string_to_color.find(this->colors[i].tag);
			if(position > -1)
			{
				string_to_color.replace(position, tag_length, this->colors[i].code);
			}			
		}
		while(position != -1);
	}
	return string_to_color; //note: at this point string_to_color has been colorized
}
