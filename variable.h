#pragma once

#include <string>
#include <utility>

class Variable
{
	std::string name;
	long long value{};

public:
	Variable() = default;
	Variable(std::string id, long long value) : name(std::move(id)), value(value) {}

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
};
