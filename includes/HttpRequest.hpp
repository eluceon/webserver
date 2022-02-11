#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <string>

# define LINE_END "\r\n"
# define LINE_DOUBLE_END "\r\n\r\n"

namespace ft
{
	class HttpRequest {
		public:
			HttpRequest();
			HttpRequest(const HttpRequest& other);
			HttpRequest(const char* str);
			~HttpRequest();

			HttpRequest& operator=(const HttpRequest other);

			std::string	getMethodName() const;
			std::string	getVersionName() const;
			int			setBadRequest(int status);
			void		setStatus(int status);
			int			getStatus() const;
			bool 		setMethod(std::string& requestMethod);
			bool		setVersion(std::string& protocolVersion);
			int			parse(const std::string& messages);
			bool		parseStartLine(const std::string& request);

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
			int			_protocolVersion;
			std::string	_uri;
			bool		_parsed;
			int			_status;
	};
}

#endif