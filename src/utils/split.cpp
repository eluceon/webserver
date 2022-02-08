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
	**	split a std::string into a std::vector<std::string>
	*/
	std::vector<std::string>	split(const std::string& str) {
		std::string::const_iterator itBegin;
		std::string::const_iterator itEnd;
		std::vector<std::string> splitedStrings;

		itBegin = str.begin();
		while((itBegin = std::find_if(itBegin, str.end(), notSpace)) != str.end()) {
			itEnd = std::find_if(itBegin, str.end(), space);
			splitedStrings.push_back(std::string(itBegin, itEnd));
			itBegin = itEnd;
		}
		return splitedStrings;
	}
}