#pragma once

#include <string>
#include <vector>

class Variable
{
	std::string name;
	long long value;
	std::string str_value = "";

public:
	Variable() = default;
	Variable(std::string id, long long value) : name(id), value(value) {}
	Variable(std::string id, std::string value) : name(id), str_value(value) {}

	std::string getName() const
	{
		return this->name;
	}

	long long getValue() const
	{
		return this->value;
	}

	void setValue(long long val)
	{
		this->value = val;
	}

	std::string getStrValue() const
	{
		return this->str_value;
	}

	void setStrValue(const std::vector<char>& char_list)
	{
		for (const char c : char_list)
			this->str_value += c;
	}
};
