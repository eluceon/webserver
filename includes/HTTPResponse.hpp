#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include "Config.hpp"
# include "HTTPRequest.hpp"
# include "VirtualHost.hpp"
# include "Location.hpp"
# include "utils.hpp"
# include <unistd.h>
# include <fcntl.h>

namespace ft {
    class HTTPResponse {
    private:
        HTTPRequest*							_req;
        std::map<std::string,ft::VirtualHost>	&_vhost;
        std::string								_resource;
		std::string 							_res_path;
		std::vector<std::string> 				_index;
		bool 									_autoindex;
        std::map<std::string, std::string>		_headers;

//        HTTPResponse(const HTTPResponse &x);
//        HTTPResponse &operator=(const HTTPResponse &x);
		void 		init(void);
		void 		getParams(const std::string &server_name);
        std::string getMIME(std::string file);
		bool validMethod(std::string &method);
		std::string GetResponse(void);
		std::string getError(size_t code);
        std::string getStatus(size_t code);
		std::string sendGet(void);
		std::string sendPost(void);
		std::string sendDelete(void);
    public:
        HTTPResponse(HTTPRequest* req, std::map<std::string,ft::VirtualHost> &vhost);
        ~HTTPResponse(void);
        std::string getResponse(void);
    };
}


# endif