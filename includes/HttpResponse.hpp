#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <fstream>
# include <unordered_map>
# include "HttpRequest.hpp"
# include "VirtualHost.hpp"

namespace ft {
	class HttpResponse {
		public:
			// HttpResponse(HttpRequest* httpReuest);
			HttpResponse(
				HttpRequest* httpReuest,
				std::unordered_map<std::string,ft::VirtualHost>	&_virtualHosts
			);
			HttpResponse(const HttpResponse &other);
			~HttpResponse();

			HttpResponse &operator=(const HttpResponse &other);
			
			const std::string&	getResponse();
		protected:
			HttpRequest* 											_httpReuest;
			std::unordered_map<std::string,ft::VirtualHost>			&_virtualHosts;
			std::string												_response;

			HttpResponse();

			void	run();
			void	handleGetResponse();
			void	handlePostResponse();
			void	handleDeleteResponse();
			void	setErrorResponse(int status, const std::string& description);

			void	printConfigurations(); 	// DELETE THIS METHOD!
	};
	
} // namespace ft


#endif