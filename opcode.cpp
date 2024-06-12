#include "opcode.h"

std::map<std::string, Variable> scope;

long long Opcode::index(const std::string& var_name)
{
	return scope[var_name].getValue();
}

void Opcode::set(std::string operand1, const std::string& modifier, const std::string& operand2)
{
	if (modifier != ":=")
		return;

	Variable var = Variable(operand1, std::stoll(operand2));
	scope.insert({ var.getName(), var });
}

void Opcode::move(const std::string& operand1, const std::string& modifier, const std::string& operand2)
{
	if (modifier != "->")
		return;

	if (operand1 == "STDIN")
	{
		std::string input;
		std::getline(std::cin, input);

		try
		{
			scope[operand2].setValue(std::stoll(input));
		}
		catch (const std::invalid_argument& _)
		{
			std::vector<char> characters(input.begin(), input.end());
			for (const char c : input)
				characters.emplace_back(c);
			scope[operand2].setStrValue(characters);
		}
	}
	else if (operand2 == "STDOUT")
	{
		const Variable var = scope[operand1];
		if (!var.getStrValue().empty())
			std::cout << var.getStrValue() << '\n';
		else
			std::cout << var.getValue() << '\n';
	}
	else
	{
		const Variable var = scope[operand1];
		scope[operand2].setValue(var.getValue());
	}
}

void Opcode::arithmetic(const std::string& operand1, const std::string& modifier, const std::string& operand2)
{
	if (modifier == "+")
	{
		const Variable var1 = scope[operand1];
		Variable var2 = scope[operand2];
		var2.setValue(var1.getValue() + var2.getValue());
		scope.erase(var2.getName());
		scope.insert({ var2.getName(), var2 });
	}
	else if (modifier == "-")
	{
		const Variable var1 = scope[operand1];
		Variable var2 = scope[operand2];
		var2.setValue(var1.getValue() - var2.getValue());
		scope.erase(var2.getName());
		scope.insert({ var2.getName(), var2 });
	}
	else if (modifier == "*")
	{
		const Variable var1 = scope[operand1];
		Variable var2 = scope[operand2];
		var2.setValue(var1.getValue() * var2.getValue());
		scope.erase(var2.getName());
		scope.insert({ var2.getName(), var2 });
	}
	else if (modifier == "/")
	{
		const Variable var1 = scope[operand1];
		Variable var2 = scope[operand2];
		var2.setValue(var1.getValue() / var2.getValue());
		scope.erase(var2.getName());
		scope.insert({ var2.getName(), var2 });
	}
}

void Opcode::str(std::string operand1, const std::string& modifier, const std::string& operand2)
{
	if (modifier != "=")
		return;

	const std::vector<std::string> chars = Tokenizer::split(operand2, ",");
	std::vector<char> export_e;
	Variable newString = Variable(std::move(operand1), "");
	scope.insert({ newString.getName(), newString });

	for (const auto& i : chars)
	{
		Variable var = scope[i];
		char j = static_cast<char>(var.getValue());
		export_e.push_back(j);
	}

	newString.setStrValue(export_e);
	scope.erase(newString.getName());
	scope.insert({ newString.getName(), newString });
}

long long Opcode::conditional(const std::string& operand1, const std::string& modifier)
{
	const std::vector<std::string> statement = Tokenizer::split(modifier, "=");
	const Variable var1 = scope[std::string(1, statement[0].at(0))];
	const Variable var2 = scope[statement[1]];

	try
	{
		if (std::string(1, statement[0].at(1)) == "!")
		{
			if (var1.getValue() != var2.getValue())
				return NULL;
			return std::stoll(operand1) + 1;
		}

		if (std::string(1, statement[0].at(1)) == "<")
		{
			if (var1.getValue() <= var2.getValue())
				return NULL;
			return std::stoll(operand1) + 1;
		}

		if (std::string(1, statement[0].at(1)) == ">")
		{
			if (var1.getValue() >= var2.getValue())
				return NULL;
			return std::stoll(operand1) + 1;
		}
	}
	catch (std::out_of_range& _)
	{
		if (var1.getValue() == var2.getValue())
			return NULL;
		return std::stoll(operand1) + 1;
	}

	return NULL;
}

void Opcode::del(const std::string& operand)
{
	const Variable var = scope[operand];
	scope.erase(var.getName());
}