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
		std::map<std::string, std::string>		_headers;
		std::string 							_res;
		std::string 							_res_path;
		std::string 							_location;
		std::vector<std::string> 				_index;
		bool 									_autoindex;
		std::string 							_fastCGI;

//        HTTPResponse(const HTTPResponse &x);
        HTTPResponse &operator=(const HTTPResponse &x);
		void 		init(void);
		std::string cleanURI(std::string rel_path);
		void 		getParams(void);
		bool 		isCGIRequest(void);
        std::string getMIME(std::string file);
		bool validMethod(std::string &method);
		std::string GetResponse(size_t code, const char *content, size_t content_size);
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