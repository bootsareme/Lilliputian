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
	std::vector<Instruction> instructions;
	std::vector<std::string> opcodes;
	std::vector<std::string> arg1, arg2;
	std::vector<std::string> modifier;
	
	for (std::string line; std::getline(src, line);)
	{
		//std::string pos1 = line.substr(0, line.find(' '));
		std::vector<std::string> token = Tokenizer::split(line, " ");

		if (token.size() > 3)
			instructions.emplace_back(Instruction{ token[0], token[1], token[2], token[3] });
		else if (token.size() > 2)
			instructions.emplace_back(Instruction{ token[0], token[1], token[2], "`" });
		else if (token.size() > 1)
			instructions.emplace_back(Instruction{ token[0], token[1], "`", "`" });
		else
			instructions.emplace_back(Instruction{ token[0], "`", "`", "`" });
	}

	Tokenizer::analyze(instructions);
}

void Tokenizer::analyze(std::vector<Instruction> instructions)
{	
	size_t lines;

	for (size_t i = 0; i < instructions.size(); i++)
	{
		if (instructions[i].opcode == "SET")
			Opcode::set(instructions[i].operand1, instructions[i].modifier, instructions[i].operand2);
		else if (instructions[i].opcode == "MOV")
			Opcode::move(instructions[i].operand1, instructions[i].modifier, instructions[i].operand2);
		else if (instructions[i].opcode == "ARITH")
			Opcode::arithmetic(instructions[i].operand1, instructions[i].modifier, instructions[i].operand2);
		else if (instructions[i].opcode == "STR")
			Opcode::str(instructions[i].operand1, instructions[i].modifier, instructions[i].operand2);
		else if (instructions[i].opcode == "DEL")
			Opcode::del(instructions[i].operand1);
		else if (instructions[i].opcode == "INT")
			std::this_thread::sleep_for(std::chrono::milliseconds(std::stoll(instructions[i].operand1)));
		else if (instructions[i].opcode == "CHECK") {
			if (Opcode::conditional(instructions[i].operand1, instructions[i].modifier) != NULL)
			{
				lines = i + Opcode::conditional(instructions[i].operand1, instructions[i].modifier);
				goto _dst_;
			}
		}
		else if (instructions[i].opcode == "JMP")
		{
			try
			{
				lines = std::stoll(instructions[i].operand1);
			}
			catch (std::invalid_argument& _)
			{
				lines = Opcode::index(instructions[i].operand1);
			}
			goto _dst_;
		}
	}
	return;

_dst_:
	for (size_t i = lines - 1; i < instructions.size(); i++)
	{
		if (instructions[i].opcode == "SET")
			Opcode::set(instructions[i].operand1, instructions[i].modifier, instructions[i].operand2);
		else if (instructions[i].opcode == "MOV")
			Opcode::move(instructions[i].operand1, instructions[i].modifier, instructions[i].operand2);
		else if (instructions[i].opcode == "ARITH")
			Opcode::arithmetic(instructions[i].operand1, instructions[i].modifier, instructions[i].operand2);
		else if (instructions[i].opcode == "STR")
			Opcode::str(instructions[i].operand1, instructions[i].modifier, instructions[i].operand2);
		else if (instructions[i].opcode == "DEL")
			Opcode::del(instructions[i].operand1);
		else if (instructions[i].opcode == "INT")
			std::this_thread::sleep_for(std::chrono::milliseconds(std::stoll(instructions[i].operand1)));
		else if (instructions[i].opcode == "CHECK") {
			if (Opcode::conditional(instructions[i].operand1, instructions[i].modifier) != NULL)
			{
				lines = i + Opcode::conditional(instructions[i].operand1, instructions[i].modifier);
				goto _dst_;
			}
		} else if (instructions[i].opcode == "JMP")
		{
			try
			{
				lines = std::stoll(instructions[i].operand1);
			}
			catch (std::invalid_argument& _)
			{
				lines = Opcode::index(instructions[i].operand1);
			}
			goto _dst_;
		}
	}
}