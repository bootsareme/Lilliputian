#pragma once

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "variable.h"
#include "tokenizer.h"

namespace Opcode
{
	long long index(const std::string& var_name);
	void set(std::string operand1, const std::string& modifier, const std::string& operand2);
	void move(const std::string& operand1, const std::string& modifier, const std::string& operand2);
	void arithmetic(const std::string& operand1, const std::string& modifier, const std::string& operand2);
	void str(std::string operand1, const std::string& modifier, const std::string& operand2);
	long long conditional(const std::string& operand1, const std::string& modifier);
	void del(const std::string& operand);
}