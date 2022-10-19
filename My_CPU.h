#ifndef MY_CPU_H
# define MY_CPU_H

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <map>

# include "Utils.h"

class MY_CPU
{
	public:
		MY_CPU(const std::string& path);

		struct CPU
		{
			std::map<const std::string, int> registers = {
				{"R1", 0},
				{"R2", 0},
				{"R3", 0},
				{"R4", 0},
				{"R5", 0},
				{"R6", 0},
				{"R7", 0},
				{"R8", 0},
				{"R9", 0},
				{"R10", 0}
			};
			int flag = 0;
		};
		

	private:
		//private section for member functions
		void Parsing();

		void FindRemoveLabels();

		void execute();

		void PrintReg();

		friend void InitMapFun(std::map<std::string, void(*)(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& index)>& my_function);

		//instructions
		//---------------------------------------
		friend void Mov(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Add(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Sub(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Mul(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Div_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);

		friend void And_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Or_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Xor_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Test(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Cmp(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Not_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);

		friend void Inc(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Dec(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);

		friend void Je_Jz(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Jne_Jnz(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Jg_Jnle(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Jge_Jnl(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Jl_Jnge(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		friend void Jle_Jng(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i);
		//---------------------------------------
	private:
		std::ifstream my_fileName;
		std::map<size_t, std::vector<std::string>> my_file;
		std::map<std::string, size_t> my_labels;
		CPU my_cpu;
};

#endif