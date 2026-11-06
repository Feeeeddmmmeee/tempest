#include "InputParser.h"

InputParser::InputParser(int argc, char *argv[])
{
	for(int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		if(arg.starts_with('-'))
		{
			if(i + 1 < argc && !(std::string(argv[i+1]).starts_with('-')))
			{
				options[arg] = argv[++i];
				continue;
			}

			options[arg] = "";
		}
	}
}

bool InputParser::has(const std::string &flag) const
{
	return options.find(flag) != options.end();
}

bool InputParser::hasValue(const std::string &flag) const
{
	auto it = options.find(flag);
	if(it == options.end()) return 0;
	return it->second != "";
}

std::string InputParser::get(const std::string &flag) const
{
	auto it = options.find(flag);
	if(it == options.end()) return "";
	return it->second;
}

std::string InputParser::getOr(const std::string &init, const std::string &flag) const
{
	if(hasValue(flag))
		return get(flag);

	return init;
}

std::string InputParser::getOr(const std::string &init, const std::string &flag, const std::string &flag2) const
{
	if(hasValue(flag))
		return get(flag);
	if(hasValue(flag2))
		return get(flag2);

	return init;
}
