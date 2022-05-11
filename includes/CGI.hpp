#ifndef CGI_HPP
# define CGI_HPP

#include "Server.hpp"
# include <unistd.h>

namespace ft {
	class CGI {
	private:
		CGI(void);
		CGI(const CGI &x);
		CGI &operator=(const CGI &x);

		HTTPRequest*	_req;
		char		**_envp;
		std::string _res;
		std::string _res_path;
		std::map<std::string, std::string> _headers;
	public:
		CGI(std::string &res, std::string &res_path, std::map<std::string, std::string> &headers, HTTPRequest* req);
		~CGI();
		std::string execCGI();
	};
}
#endif
