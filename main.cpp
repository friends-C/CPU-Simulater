#include "My_CPU.h"
#include "Utils.h"
#include <regex>

static void CheckFile(int ac, const std::string& path)
{
	if (ac == 2) {
		std::cmatch result;
		std::regex regular("(.myasm)");
		if (std::regex_search(path.c_str(), result, regular) == 0) {
			Utils::PrintError(2, 0);
		}
	} else {
		Utils::PrintError(1, 0);
	}
}

int main(int ac, char* av[])
{
	CheckFile(ac, av[1]);
	MY_CPU fCPU(av[1]);
	return 0;
}

	// for (size_t i = 1; i <= my_file.size(); ++i) {
	// 	for (size_t j = 0; j < my_file[i].size(); ++j) {
	// 		std::cout << my_file[i][j] << "   ";
	// 	}
	// 	std::cout<<std::endl;
	// }