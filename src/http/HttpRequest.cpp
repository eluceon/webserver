#include "HttpRequest.hpp"

ft::HttpRequest::HttpRequest() {
	// _method = setMethod("GET");
	// _uri = "/";
	// _version = setVersion("HTTP/1.1");
}

std::string	ft::HttpRequest::getMethodName() const {
	switch (_method)
	{
	case GET:
		return "GET";
	case POST:
		return "POST";
	case DELETE:
		return "DELETE";
	case PUT:
		return "PUT";
	default:
		return "";
	}
}

std::string ft::HttpRequest::getVersionName() const {
	switch (_version)
	{
	case HTTP_1_0:
		return "HTTP/1.0";
	case HTTP_1_1:
		return "HTTP/1.1";
	case HTTP_2_0:
		return "HTTP/2.0";
	default:
		return "";
	}
}

bool ft::HttpRequest::setMethod(const std::string& method) {
	for(int i = 0; i < NUMBER_OF_METHODS; ++i) {
		if(method.compare(getMethodName()) == 0)
			return true;
	}
	return false;
}

bool ft::HttpRequest::setVersion(const std::string& version) {
	for(int i = 0; i < NUMBER_OF_VERSIONS; ++i) {
		if(version.compare(getVersionName()) == 0)
			return true;
	}
	return false;
}
