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
		std::string::size_type		len = str.length();

		do {
			pos = str.find(delim, prev);
			if (pos != prev)
				splitedStrings.push_back(str.substr(prev, pos - prev));
			prev = pos != std::string::npos ? pos + delim.size() : std::string::npos;
		} while (prev < len);
    	return splitedStrings;
	}

	/*
	**	Converts a string to upper sase
	*/
	void	toUpperString(std::string& str) {
		std::transform(str.begin(), str.end(), str.begin(), toupper);
	}

	/*
	**	Converts a string to lower sase
	*/
	void	toLowerString(std::string& str) {
		std::transform(str.begin(), str.end(), str.begin(), tolower);
	}

	/*
	**	Returns remainder of the string after delimeter
	*/
	std::string	getExtension(const std::string& str,
                                    const std::string& delim)
	{
		std::string::size_type		pos;

		pos = str.find(delim);
		if (pos == std::string::npos)
        	return "";
   		else
        	return str.substr(pos + delim.size());
	}

	/*
	**	Returns the begining of the string before delimeter
	*/
	std::string	getWithoutExtension(const std::string& str,
                                    	const std::string& delim)
	{
		std::string::size_type		pos;

		pos = str.find(delim);
		if (pos == std::string::npos)
        	return str;
   		else
        	return str.substr(0, pos);
	}
}