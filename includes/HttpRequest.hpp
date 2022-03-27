#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <string>
# include <vector>
# include <map>
# include "HttpConstants.hpp"

# define CRLF				"\r\n"
# define CRLF_CRLF			"\r\n\r\n"
# define PROTOCOL			"http"

namespace ft
{
	class HttpRequest {
		public:
			HttpRequest();
			HttpRequest(const HttpRequest &other);
			HttpRequest(const char* str);
			~HttpRequest();

			HttpRequest &operator=(const HttpRequest &other);

			void 				setMethod(std::string requestMethod);
			std::string			getMethodName() const;
			void				setHTTPVersion(std::string HTTPVersion);
			std::string			getHTTPVersion() const;
			int					setBadRequest(int status);
			void				setStatus(int status);
			int					getStatus() const;
			void				setURI(const std::string& requestURI);
			const std::string&	getProtocol() const;
			bool				setPort(const std::string& port);
			int					getPort() const;
			const std::string&	getServerName() const;
			const std::string&	getRelativePath() const;
			const std::string&	getQueryString() const;
			std::string			getFullURL() const;
			bool				isParsed() const;
			const std::map<std::string, std::string>&	getHeaders() const;
   			const std::string&	getBody() const;
			unsigned long		getContentLength() const;
			int					parse(const std::string& messages);
			const std::string&	getRequestLine() const;

		protected:
			enum e_versions
			{
				HTTP_0_9,
    			HTTP_1_0,
    			HTTP_1_1,
    			HTTP_2_0,
				NUMBER_OF_VERSIONS
			};

			std::string							_requestLine;
			int									_requestMethod;
			std::string							_requestURI;
			int									_HTTPVersion;
			std::string							_protocol;
			std::string							_serverName;
			std::string							_relativePath;
			std::string							_queryString;
			int									_port;
			std::map<std::string, std::string>	_headers;
			std::string							_body;
			bool								_parsed;
			int									_status;
			bool								_chunked;
			unsigned long						_contentLength;
			unsigned long						_clientMaxBodySize;

			void				parseRequestLine(const std::string& request);
			void				parseHeaders(const std::vector<std::string>& headerLines);
			void				parseBody(const std::string& body);
			void				parseChunkedBody(const std::string& body);
			void				processHeaders(void);
	};
}

#endif