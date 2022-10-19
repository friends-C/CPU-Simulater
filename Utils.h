#ifndef UTILS_H
# define UTILS_H

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include "My_CPU.h"

namespace Utils
{
	void PrintError(const int error_number, const size_t line);
	void ToUpper(std::string& str);
	bool IsNumber(const std::string& str);
	std::vector<std::string> SplitText(const std::string& str);
	std::string GetLabel(std::string& line, const size_t line_num);
}

#endif