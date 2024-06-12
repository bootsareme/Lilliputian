#pragma once

#include <fstream>
#include <thread>
#include <chrono>

#include "opcode.h"
#include "variable.h"

typedef struct
{
	std::string opcode;
	std::string operand1;
	std::string modifier;
	std::string operand2;
} Instruction;

namespace Tokenizer 
{
	std::vector<std::string> split(const std::string& str, const std::string& delim);
	void parse(std::ifstream& src);
	void analyze(std::vector<Instruction> instructions);
}