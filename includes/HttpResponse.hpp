#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <fstream>
# include <unordered_map>
# include "HTTPRequest.hpp"
# include "VirtualHost.hpp"

namespace ft {
	class HTTPResponse {
		public:
			// HTTPResponse(HTTPRequest* httpReuest);
			HTTPResponse(
				HTTPRequest* httpReuest,
				std::unordered_map<std::string,ft::VirtualHost>	&_virtualHosts
			);
			HTTPResponse(const HTTPResponse &other);
			~HTTPResponse();

			HTTPResponse &operator=(const HTTPResponse &other);
			
			const std::string&	getResponse();
		protected:
			HTTPRequest* 											_httpReuest;
			std::unordered_map<std::string,ft::VirtualHost>			&_virtualHosts;
			std::string												_response;

			HTTPResponse();

			void	run();
			void	handleGetResponse();
			void	handlePostResponse();
			void	handleDeleteResponse();
			void	setErrorResponse(int status, const std::string& description);

			void	printConfigurations(); 	// DELETE THIS METHOD!
	};
	
} // namespace ft


#endif