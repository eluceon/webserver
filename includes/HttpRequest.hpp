#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <string>

# define LINE_END			"\r\n"
# define LINE_DOUBLE_END	"\r\n\r\n"
# define DEFAULT_PORT		80
# define PROTOCOL			"http"

namespace ft
{
	class HttpRequest {
		public:
			HttpRequest();
			HttpRequest(const HttpRequest& other);
			HttpRequest(const char* str);
			~HttpRequest();

			HttpRequest& operator=(const HttpRequest other);

			bool 				setMethod(std::string requestMethod);
			std::string			getMethodName() const;
			bool				setVersion(std::string protocolVersion);
			std::string			getVersionName() const;
			int					setBadRequest(int status);
			void				setStatus(int status);
			int					getStatus() const;
			int					parse(const std::string& messages);
			bool				parseStartLine(const std::string& request);
			bool				setURI(const std::string& requestURI);
			const std::string&	getProtocol() const;
			bool				setPort(const std::string& port);
			int					getPort() const;
			const std::string&	getServerName() const;
			const std::string&	getRelativePath() const;
			const std::string&	getQueryString() const;
			std::string			getFullURL() const;

		protected:
			enum e_methods {
				GET,
				POST,
				DELETE,
				PUT,
				NUMBER_OF_METHODS
			};
			enum e_versions
			{
				HTTP_0_9,
    			HTTP_1_0,
    			HTTP_1_1,
    			HTTP_2_0,
				NUMBER_OF_VERSIONS
			};

			enum e_limits {
		        MAX_URI_LENGTH		= 2048,
   			};

			int			_requestMethod;
			std::string	_requestURI;
			int			_protocolVersion;
			std::string	_protocol;
			std::string	_serverName;
			std::string	_relativePath;
			std::string	_queryString;
			int			_port;
			bool		_parsed;
			int			_status;
	};
}

#endif