#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <fstream>
# include "HttpRequest.hpp"

namespace ft {
	class HttpResponse {
		public:
			HttpResponse();
			HttpResponse(HttpRequest* httpReuest);
			HttpResponse(const HttpResponse &other);
			~HttpResponse();

			HttpResponse &operator=(const HttpResponse &other);
			
			const std::string&	getResponse();
		protected:
			HttpRequest* _httpReuest;
			std::string	_response;

			void	run();
			void	setErrorResponse(int status, const std::string& description);
	};
	
} // namespace ft


#endif