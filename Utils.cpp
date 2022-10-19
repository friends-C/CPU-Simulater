#include "Utils.h"

void Utils::PrintError(const int error_number, const size_t line)
{

	if (error_number == 1) {
		std::cerr << "error code 01 _ !!!! Must be one input file !!!!\n";
	} else if (error_number == 2) {
		std::cerr << "error code 02 _ !!!! Wrong extension of file !!!!\n";
	} else if (error_number == 3) {
		std::cerr << "error code 03 _ !!!! Cannot opening the file !!!!\n";
	} else if (error_number == 4) {
		std::cerr << "error code 04 _ !!!! Invalid arguments in line " << line << "  !!!!\n";
	} else if (error_number == 5) {
		std::cerr << "error code 05 _ !!!! Cannot be divided by 0 !!!!\n";
	}
	exit(1);
}

bool Utils::IsNumber(const std::string& str)
{
	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] < '0' || str[i] > '9') {
			return false;
		}
	}
	return true;
}

void Utils::ToUpper(std::string& str)
{
	int i = -1;
	while (str[++i]) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		}
	}
}

std::vector<std::string> Utils::SplitText(const std::string& str)
{
	std::vector<std::string> splitedText;
	std::stringstream check(str);
	std::string line;
	while (getline(check, line, ' '))
	{
		while (line[0] == '\t' || line[0] == ' ') {
			line.erase(line.begin(), line.begin() + 1);
		}
		size_t found = line.find(',');
		Utils::ToUpper(line);
		if (found == std::string::npos && line[0] != 0) {
			splitedText.push_back(line);
		} else if (found != std::string::npos && line[0] != 0) {
			splitedText.push_back(line.substr(0, found));
			splitedText.push_back(line.substr(found + 1));
		}
	}
	return splitedText;
}

std::string Utils::GetLabel(std::string& line, const size_t line_num)
{
    std::string label_in_line = line;
	label_in_line.pop_back();
    line.clear();
    line = std::to_string(line_num);
	return label_in_line;
}

