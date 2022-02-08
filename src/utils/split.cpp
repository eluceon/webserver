#include "utils.hpp"

namespace ft
{	
	bool	space(char c) {
		return std::isspace(c);
	}
	
	bool	notSpace(char c) {
		return !std::isspace(c);
	}
	
	/*
	**	splits std::string into std::vector<std::string> by whitespaces
	*/
	std::vector<std::string>	split(const std::string& str) {
		std::string::const_iterator	itBegin;
		std::string::const_iterator	itEnd;
		std::vector<std::string>	splitedStrings;

		itBegin = str.begin();
		while((itBegin = std::find_if(itBegin, str.end(), notSpace)) != str.end()) {
			itEnd = std::find_if(itBegin, str.end(), space);
			splitedStrings.push_back(std::string(itBegin, itEnd));
			itBegin = itEnd;
		}
		return splitedStrings;
	}


	/*
	**	splits std::string into std::vector<std::string> by delimeter
	*/
	std::vector<std::string> split(const std::string& str,
                                    const std::string& delim)
	{
    	std::vector<std::string>	splitedStrings;
		std::string::size_type		pos = 0;
		std::string::size_type		prev = 0;

		while ((pos = str.find(delim, prev)) != std::string::npos) {
			splitedStrings.push_back(str.substr(prev, pos - prev));
			prev = pos + delim.size();
		}
		splitedStrings.push_back(str.substr(prev));
    	return splitedStrings;
	}
}