#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <algorithm>
# include <cstring>
# include <cstdlib>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>	/* basic system data types */
# include <sys/socket.h>	/* basic socket definitions */

# define RED_COLOR		"\033[1;31m"
# define RESET_COLOR 	"\033[0;0m"
# define GREEN_COLOR	"\033[0;32m"

namespace ft
{
    void	systemErrorExit(const std::string& mesage);
    void	errorExit(const std::string& mesage);
    int		Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
    
} // namespace ft



#endif