#include "tokenizer.h"

std::vector<std::string> Tokenizer::split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos; 

	do 
	{
		pos = str.find(delim, prev);
		if (pos == std::string::npos)
			pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty())
			tokens.emplace_back(token);
		prev = pos + delim.length();
	}
	while (pos < str.length() && prev < str.length());

	return tokens;
}

void Tokenizer::parse(std::ifstream& src) 
{
	std::vector<std::string> opcodes;
	std::vector<std::string> arg1, arg2;
	std::vector<std::string> operand;
	
	for (std::string instruction; std::getline(src, instruction);)
	{
		std::string pos1 = instruction.substr(0, instruction.find(' '));
		std::vector<std::string> token = split(instruction, " ");

		if (token.size() > 1 && token.size() > 2 && token.size() > 3) {
			opcodes.emplace_back(pos1);
			arg1.emplace_back(token[1]);
			arg2.emplace_back(token[3]);
			operand.emplace_back(token[2]);
		} else if (token.size() > 1 && token.size() > 2) {
			opcodes.emplace_back(pos1);
			arg1.emplace_back(token[1]);
			arg2.emplace_back("`");
			operand.emplace_back(token[2]);
		} else if (token.size() > 1) {
			opcodes.emplace_back(pos1);
			arg1.emplace_back(token[1]);
			arg2.emplace_back("`");
			operand.emplace_back("`");
		} else {
			opcodes.emplace_back(pos1);
			arg1.emplace_back("`");
			arg2.emplace_back("`");
			operand.emplace_back("`");
		}
	}
	link(opcodes, arg1, operand, arg2);
}

void Tokenizer::link(std::vector<std::string> instruction, std::vector<std::string> arg1,
	std::vector<std::string> modifier, std::vector<std::string> arg2)
{	
	size_t lines;

	for (long long i = 0; i < instruction.size(); i++) {
		if (instruction[i] == "SET")
			Opcode::set(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "MOV")
			Opcode::move(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "ARITH")
			Opcode::add(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "STR")
			Opcode::str(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "PRINT")
			Opcode::print(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "DEL")
			Opcode::del(arg1[i]);
		else if (instruction[i] == "INT")
			std::this_thread::sleep_for(std::chrono::milliseconds(std::stoll(arg1[i])));
		else if (instruction[i] == "CHECK") {
			if (Opcode::conditional(arg1[i], modifier[i]) != NULL) {
				lines = i + Opcode::conditional(arg1[i], modifier[i]);
				goto _thread;
			}
		}
		else if (instruction[i] == "JMP") {
			try
			{
				lines = std::stoll(arg1[i]);
			}
			catch (std::invalid_argument& _)
			{
				lines = Opcode::index(arg1[i]);
			}
			goto _thread;
		}
	}
	return;

_thread:
	for (long long i = lines - 1; i < instruction.size(); i++) {
		if (instruction[i] == "SET")
			Opcode::set(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "MOV")
			Opcode::move(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "ARITH")
			Opcode::add(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "STR")
			Opcode::str(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "PRINT")
			Opcode::print(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "DEL")
			Opcode::del(arg1[i]);
		else if (instruction[i] == "INT")
			std::this_thread::sleep_for(std::chrono::milliseconds(std::stoll(arg1[i])));
		else if (instruction[i] == "CHECK") {
			if (Opcode::conditional(arg1[i], modifier[i]) != NULL) {
				lines = i + Opcode::conditional(arg1[i], modifier[i]);
				goto _thread;
			}
		} else if (instruction[i] == "JMP") {
			try
			{
				lines = std::stoll(arg1[i]);
			}
			catch (std::invalid_argument& _)
			{
				lines = Opcode::index(arg1[i]);
			}
			goto _thread;
		}
	}
}