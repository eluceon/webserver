#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <string>


namespace ft
{
	class HttpRequest {
		public:
			HttpRequest();
			HttpRequest(const HttpRequest& other);
			HttpRequest(const char* str);
			~HttpRequest();

			HttpRequest& operator=(const HttpRequest other);

			std::string getMethodName() const;
			std::string getVersionName() const;
			bool setMethod(const std::string& method);
			bool setVersion(const std::string& version);

		private:
			enum e_methods {
				GET,
				POST,
				DELETE,
				PUT,
				NUMBER_OF_METHODS
			};
			enum e_versions
			{
    			HTTP_1_0,
    			HTTP_1_1,
    			HTTP_2_0,
				NUMBER_OF_VERSIONS
			};

			int			_method;
			int			_version;
			std::string	_uri;			
	};
}

#endif