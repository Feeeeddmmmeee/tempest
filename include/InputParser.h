#pragma once

#include <string>
#include <unordered_map>

class InputParser
{
	public:
		InputParser(int argc, char *argv[]);

		bool has(const std::string &flag) const;
		bool hasValue(const std::string &flag) const;

		std::string get(const std::string &flag) const;
		std::string get(const std::string &flag, const std::string &flag2) const;

		std::string getOr(const std::string &init, const std::string &flag) const;
		std::string getOr(const std::string &init, const std::string &flag, const std::string &flag2) const;

	private:
		std::unordered_map<std::string, std::string> options;
};
