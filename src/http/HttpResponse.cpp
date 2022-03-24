#include "HttpResponse.hpp"

ft::HttpResponse::HttpResponse() {}
ft::HttpResponse::HttpResponse(HttpRequest* httpReuest)
	: _httpReuest(httpReuest)
{
	run();
}
ft::HttpResponse::HttpResponse(const HttpResponse& other) {}
ft::HttpResponse::~HttpResponse() {}


// HttpResponse	&ft::HttpResponse::operator=(const HttpResponse& other) {
// 	if (this != &other) {
// 		// some logic here
// 	}
// 	return *this;
// }


void ft::HttpResponse::run() {
	if (!_httpReuest->getMethodName().compare("GET")) {
		if (_httpReuest->getStatus() == HTTP_OK ) {
			// _httpReuest->getRelativePath();
			std::ifstream	siteFile("./www/site1/index.html");
			if ((siteFile.rdstate() & std::ifstream::failbit) != 0 ) {
				setErrorResponse(HTTP_NOT_FOUND, "NOT FOUND");
			} else {
				_response = _httpReuest->getHTTPVersion() + " 200 OK\r\n";
				_response += "Server: ft_server\r\n\r\n";
				std::string line;
				while (getline (siteFile, line))
					_response.append(line);
   				siteFile.close();
			}
		} else if (!_httpReuest->getMethodName().compare("POST")) {

		} else if (!_httpReuest->getMethodName().compare("DELETE")) {

		} 
	}
}

void ft::HttpResponse::setErrorResponse(int status, const std::string& description) {
	std::string	statusCode = std::to_string(status);

	_response =  _httpReuest->getHTTPVersion() + ' ' + statusCode + ' ' + description + "\r\n";
	_response += "Server: Tiny webserver\r\n\r\n";
	_response += "<html><head><title> " +  statusCode + ' ' + description + "</title></head>\
		<body><h1>ERROR " + description + "</h1></body></html>\r\n";
}

const std::string&	ft::HttpResponse::getResponse() {
	return _response;
}


