#ifndef CGI_HPP
# define CGI_HPP

# include <iostream>
# include <string>
# include <unistd.h>
# include <sys/wait.h>
# include "HTTPResponse.hpp"

namespace ft {
	class CGI {
	private:
		CGI(void);
		CGI(const CGI &x);
		CGI &operator=(const CGI &x);

		std::string _res;
		std::string _res_path;
		HTTPRequest*	_req;
//		std::map<std::string, std::string> _headers;
	public:
		CGI(std::string &res, std::string &res_path, HTTPRequest* req);
		~CGI();
		std::string execCGI();
	};
}
#endif
