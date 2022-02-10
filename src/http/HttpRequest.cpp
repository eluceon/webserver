#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "utils.hpp"

ft::HttpRequest::HttpRequest() {
	// _method = setMethod("GET");
	// _uri = "/";
	// _version = setVersion("HTTP/1.1");
}

ft::HttpRequest::~HttpRequest() {}

std::string	ft::HttpRequest::getMethodName() const {
	switch (_requestMethod)
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
	switch (_protocolVersion)
	{
		case HTTP_0_9:
			return "HTTP/0.9";
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

bool ft::HttpRequest::setMethod(const std::string& requestMethod) {
	for(int i = 0; i < NUMBER_OF_METHODS; ++i) {
		if(requestMethod.compare(getMethodName()) == 0)
			return true;
	}
	return false;
}

bool ft::HttpRequest::setVersion(const std::string& protocolVersion) {
	for(int i = 0; i < NUMBER_OF_VERSIONS; ++i) {
		if(protocolVersion.compare(getVersionName()) == 0)
			return true;
	}
	return false;
}

void	ft::HttpRequest::setStatus(int status) {
	_status = status;
}

int	ft::HttpRequest::setBadRequest(int status) {
	setStatus(status);
	_parsed = true;
	return status;
}

int	ft::HttpRequest::parse(const std::string& messages) {
	std::vector<std::string> segments = ft::split(messages, LINE_DOUBLE_END);
	if (segments.size() < 1)
    	return setBadRequest(HttpResponse::BAD_REQUEST);
	std::vector<std::string> headerLines = ft::split(segments[0], LINE_END);

	for (int i = 0; i < segments.size(); ++i)			// DELETE ME LATER!!! It's for testing!!!
		std::cout << segments[i];
	std::cout << "segments: " << segments.size() << '\n';
	return 0; 	///CHANGE ME LATER!!!!!!!
}



