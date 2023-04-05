#pragma once

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <utility>

#include "variable.h"
#include "str.h"

namespace Opcode
{
	long long index(const std::string& var_name);
	void set(std::string operand1, const std::string& modifier, const std::string& operand2);
	void move(const std::string& operand1, const std::string& modifier, const std::string& operand2);
	void add(const std::string& operand1, const std::string& modifier, const std::string& operand2);
	void str(std::string operand1, const std::string& modifier, const std::string& operand2);
	void print(const std::string& operand1, const std::string& modifier, const std::string& operand2);
	long long conditional(const std::string& operand1, const std::string& modifier);
	void del(const std::string& operand1);
}