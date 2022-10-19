#include "My_CPU.h"
#include "Utils.h"

MY_CPU::MY_CPU(const std::string& path)
: my_fileName(path)
{
	if (my_fileName.is_open() == 0) {
		Utils::PrintError(3, 0);
	}
	std::string line;
	size_t index = 0;
	while (std::getline(my_fileName, line)) {
		my_file[++index] = Utils::SplitText(line);
		line.clear();
	}
	Parsing();
}

void MY_CPU::Parsing()
{
	std::string labelsInLine;
	size_t found;
	for (size_t i = 1; i <= my_file.size(); ++i) {
		found = my_file[i][0].find(':');
		if (found == std::string::npos) {
			continue ;
		} else {
			labelsInLine = Utils::GetLabel(my_file[i][0], i);
			if (my_labels.find(labelsInLine) == my_labels.end()) {
                my_labels[labelsInLine] = i;
            } else {
                Utils::PrintError(4, i);
            }
		}
	}
	FindRemoveLabels();
	execute();
}


void MY_CPU::FindRemoveLabels()
{
	for (size_t i = 1; i <= my_file.size(); ++i) {
		if (my_file[i][0][0] == 'J') {
			if (my_labels.find(my_file[i][1]) != my_labels.end()) {
				my_file[i][1] = std::to_string(my_labels[my_file[i][1]]);
			}
		}
	}
}

void MY_CPU::execute()
{
	std::map<std::string, void(*)(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& index) > my_function;
	InitMapFun(my_function);
	bool flag = true;
	char smb;
	for (size_t i = 1; i <= my_file.size(); ++i)
	{
		if (my_file[i].size() == 1) {
			continue ;
		} else {
			if (my_function.find(my_file[i][0]) != my_function.end()) {
				my_function[my_file[i][0]](my_file[i], my_cpu, i);
			} else {
				Utils::PrintError(4, i);
			}
			if (flag == true) {
				smb = std::getchar();
				if (smb == '\n') {
					PrintReg();
				} else if (smb == 'q') {
					flag = false;
				}
			}
		}
	}
	if (flag == false) {
		PrintReg();
	}
}

void MY_CPU::PrintReg()
{
	std::cout << "R1" << " = " << my_cpu.registers["R1"] << std::endl;
	std::cout << "R2" << " = " << my_cpu.registers["R2"] << std::endl;
	std::cout << "R3" << " = " << my_cpu.registers["R3"] << std::endl;
	std::cout << "R4" << " = " << my_cpu.registers["R4"] << std::endl;
	std::cout << "R5" << " = " << my_cpu.registers["R5"] << std::endl;
	std::cout << "R6" << " = " << my_cpu.registers["R6"] << std::endl;
	std::cout << "R7" << " = " << my_cpu.registers["R7"] << std::endl;
	std::cout << "R8" << " = " << my_cpu.registers["R8"] << std::endl;
	std::cout << "R9" << " = " << my_cpu.registers["R9"] << std::endl;
	std::cout << "R10" << " = " << my_cpu.registers["R10"] << std::endl;
	std::cout << "Flag" << " = " << my_cpu.flag << std::endl;
}

void Mov(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (Utils::IsNumber(code[2])) {
		instructions.registers[code[1]] = std::stoi(code[2]);
	} else if (instructions.registers.find(code[2]) != instructions.registers.end()){
		instructions.registers[code[1]] = instructions.registers[code[2]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Sub(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (Utils::IsNumber(code[2])) {
		instructions.registers[code[1]] -= std::stoi(code[2]);
	} else if (instructions.registers.find(code[2]) != instructions.registers.end()){
		instructions.registers[code[1]] -= instructions.registers[code[2]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Add(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (Utils::IsNumber(code[2])) {
		instructions.registers[code[1]] += std::stoi(code[2]);
	} else if (instructions.registers.find(code[2]) != instructions.registers.end()){
		instructions.registers[code[1]] += instructions.registers[code[2]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Mul(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (Utils::IsNumber(code[2])) {
		instructions.registers[code[1]] *= std::stoi(code[2]);
	} else if (instructions.registers.find(code[2]) != instructions.registers.end()){
		instructions.registers[code[1]] *= instructions.registers[code[2]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Div_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (Utils::IsNumber(code[2])) {
		if (std::stoi(code[2]) != 0) {
			instructions.registers[code[1]] /= std::stoi(code[2]);
		} else {
			Utils::PrintError(5, i);
		}
	} else if (instructions.registers.find(code[2]) != instructions.registers.end()){
		if (instructions.registers[code[1]] != 0) {
			instructions.registers[code[1]] /= instructions.registers[code[2]];
		} else {
			Utils::PrintError(5, i);
		}
	} else {
		Utils::PrintError(4, i);
	}
}

void And_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (Utils::IsNumber(code[2])) {
		instructions.registers[code[1]] &= std::stoi(code[2]);
	} else if (instructions.registers.find(code[2]) != instructions.registers.end()){
		instructions.registers[code[1]] &= instructions.registers[code[2]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Or_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (Utils::IsNumber(code[2])) {
		instructions.registers[code[1]] |= std::stoi(code[2]);
	} else if (instructions.registers.find(code[2]) != instructions.registers.end()){
		instructions.registers[code[1]] |= instructions.registers[code[2]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Xor_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (Utils::IsNumber(code[2])) {
		instructions.registers[code[1]] ^= std::stoi(code[2]);
	} else if (instructions.registers.find(code[2]) != instructions.registers.end()){
		instructions.registers[code[1]] ^= instructions.registers[code[2]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Cmp(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (Utils::IsNumber(code[2])) {
		instructions.flag = instructions.registers[code[1]] - std::stoi(code[2]);
	} else if (instructions.registers.find(code[2]) != instructions.registers.end()){
		instructions.flag = instructions.registers[code[1]] - instructions.registers[code[2]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Not_(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (instructions.registers.find(code[2]) != instructions.registers.end()){
		instructions.registers[code[1]] = ~instructions.registers[code[1]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Dec(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (instructions.registers.find(code[1]) != instructions.registers.end()){
		--instructions.registers[code[1]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Inc(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (instructions.registers.find(code[1]) != instructions.registers.end()){
		++instructions.registers[code[1]];
	} else {
		Utils::PrintError(4, i);
	}
}

void Je_Jz(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (instructions.flag == 0){
		i = std::stoi(code[1]);
	}
}

void Jne_Jnz(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (instructions.flag != 0){
		i = std::stoi(code[1]);
	}
}

void Jg_Jnle(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (instructions.flag > 0){
		i = std::stoi(code[1]);
	}
}

void Jl_Jnge(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (instructions.flag < 0){
		i = std::stoi(code[1]);
	}
}

void Jge_Jnl(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (instructions.flag >= 0){
		i = std::stoi(code[1]);
	}
}

void Jle_Jng(const std::vector<std::string>& code, MY_CPU::CPU& instructions, size_t& i)
{
	if (instructions.flag <= 0){
		i = std::stoi(code[1]);
	}
}

void InitMapFun(std::map<std::string, void(*)(const std::vector<std::string>& code,
												MY_CPU::CPU& instructions,
												size_t& index)>& my_function)
{
	my_function = {{"MOV", Mov},
					{"SUB", Sub},
					{"ADD", Add},
					{"MUL", Mul},
					{"DIV", Div_},
					{"AND", And_},
					{"OR", Or_},
					{"XOR", Xor_},
					{"CMP", Cmp},
					{"NOT", Not_},
					{"INC", Inc},
					{"DEC", Dec},
					{"JE", Je_Jz},
					{"JZ", Je_Jz},
					{"JNE", Jne_Jnz},
					{"JNZ", Jne_Jnz},
					{"JG", Jg_Jnle},
					{"JNLE", Jg_Jnle},
					{"JGE", Jge_Jnl},
					{"JNL", Jge_Jnl},
					{"JL", Jl_Jnge},
					{"JNGE", Jl_Jnge},
					{"JLE", Jle_Jng},
					{"JNG", Jle_Jng}};
}