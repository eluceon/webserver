#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <cstring>
# include <cstdlib>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>	// basic system data types
# include <sys/socket.h>	// basic socket definitions

# define RED_COLOR		"\033[1;31m"
# define GREEN_COLOR	"\033[0;32m"
# define RESET_COLOR 	"\033[0;0m"

# define WHITESPACES	" \t\n\v\f\r"

namespace ft
{
    void						systemErrorExit(const std::string& mesage);
    void						errorExit(const std::string& mesage);
    int							Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
	std::vector<std::string>	split(const std::string& str);
	std::vector<std::string> 	split(const std::string& str, const std::string& delim);
	void						toUpperString(std::string& str);
	void						toLowerString(std::string& str);
	std::string					getExtension(const std::string& str, const std::string& delim);
	std::string					getWithoutExtension(const std::string& str, const std::string& delim);
	bool						isNumber(const std::string& str);
	bool						parseToken(const std::string& src, const std::string &delim,
										std::string::size_type& beginPos, std::string &token,
										bool skipFirstWhiteSpaces = true, bool isExactDelim = false,
										std::string::size_type maxLen = std::string::npos);
	void						timestamp(const std::string& msg);
	char 						*Getcwd();
	
}

#endif