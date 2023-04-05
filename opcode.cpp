#include "opcode.h"

std::map<std::string, Variable> varMap;
std::map<std::string, STR> str_varMap;

long long Opcode::index(const std::string& var_name)
{
	return varMap[var_name].getValue();
}

std::vector<std::string> split(const std::string& str, const std::string& delim)
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
			tokens.push_back(token);
		prev = pos + delim.length();
	}
	while (pos < str.length() && prev < str.length());

	return tokens;
}

void Opcode::set(std::string operand1, const std::string& modifier, const std::string& operand2)
{
	if (modifier != "=")
		return;

	Variable var = Variable(std::move(operand1), std::stoll(operand2));
	varMap.insert({ var.getName(), var });
}

void Opcode::move(const std::string& operand1, const std::string& modifier, const std::string& operand2)
{
	if (modifier != "->")
		return;

	if (operand2 == "STDOUT") {
		const Variable var = varMap[operand1];
		std::cout << var.getValue() << '\n';
	}

	const Variable var = varMap[operand1];
	varMap[operand2].setValue(var.getValue());
}

void Opcode::add(const std::string& operand1, const std::string& modifier, const std::string& operand2)
{
	if (modifier == "+") {
		const Variable var1 = varMap[operand1];
		Variable var2 = varMap[operand2];
		var2.setValue(var1.getValue() + var2.getValue());
		varMap.erase(var2.getName());
		varMap.insert({ var2.getName(), var2 });
	}
	else if (modifier == "-") {
		const Variable var1 = varMap[operand1];
		Variable var2 = varMap[operand2];
		var2.setValue(var1.getValue() - var2.getValue());
		varMap.erase(var2.getName());
		varMap.insert({ var2.getName(), var2 });
	}
	else if (modifier == "*") {
		const Variable var1 = varMap[operand1];
		Variable var2 = varMap[operand2];
		var2.setValue(var1.getValue() * var2.getValue());
		varMap.erase(var2.getName());
		varMap.insert({ var2.getName(), var2 });
	}
	else if (modifier == "/") {
		const Variable var1 = varMap[operand1];
		Variable var2 = varMap[operand2];
		var2.setValue(var1.getValue() / var2.getValue());
		varMap.erase(var2.getName());
		varMap.insert({ var2.getName(), var2 });
	}
}

void Opcode::str(std::string operand1, const std::string& modifier, const std::string& operand2)
{
	if (modifier != "=")
		return;

	const std::vector<std::string> chars = split(operand2, ",");
	std::vector<char> export_e;
	STR newString = STR(std::move(operand1), "");
	str_varMap.insert({ newString.getName(), newString });

	for (const auto& i : chars) {
		Variable var = varMap[i];
		char j = static_cast<char>(var.getValue());
		export_e.push_back(j);
	}

	newString.setValue(export_e);
	str_varMap.erase(newString.getName());
	str_varMap.insert({ newString.getName(), newString });
}

void Opcode::print(const std::string& operand1, const std::string& modifier, const std::string& operand2)
{
	if (modifier != "->")
		return;

	if (operand2 == "STDOUT") {
		const STR var = str_varMap[operand1];
		std::cout << var.getValue() << '\n';
	}
	else {
		const STR var = str_varMap[operand1];
		std::ofstream output(operand2);
		output << var.getValue() << '\n';
		output.close();
	}
}

long long Opcode::conditional(const std::string& operand1, const std::string& modifier)
{
	const std::vector<std::string> statement = split(modifier, "=");
	const Variable var1 = varMap[std::string(1, statement[0].at(0))];
	const Variable var2 = varMap[statement[1]];

	try {
		if (std::string(1, statement[0].at(1)) == "!") {
			if (var1.getValue() != var2.getValue())
				return NULL;
			return std::stoll(operand1) + 1;
		}

		if (std::string(1, statement[0].at(1)) == "<") {
			if (var1.getValue() <= var2.getValue())
				return NULL;
			return std::stoll(operand1) + 1;
		}

		if (std::string(1, statement[0].at(1)) == ">") {
			if (var1.getValue() >= var2.getValue())
				return NULL;
			return std::stoll(operand1) + 1;
		}
	}
	catch (std::out_of_range& _) {
		if (var1.getValue() == var2.getValue())
			return NULL;
		return std::stoll(operand1) + 1;
	}

	return NULL;
}

void Opcode::del(const std::string& operand1)
{
	const STR str = str_varMap[operand1];
	const Variable var = varMap[operand1];
	str_varMap.erase(str.getName());
	varMap.erase(var.getName());
}