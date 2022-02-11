#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "utils.hpp"
#include <string>

ft::HttpRequest::HttpRequest()
	: _requestURI(""), _protocol(""), _serverName(""), _relativePath(""),
	 _port(DEFAULT_PORT), _parsed(false), _status(ft::HttpResponse::OK)
{
	_requestMethod	= setMethod("GET");
	_protocolVersion = setVersion("HTTP/1.1");

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

bool ft::HttpRequest::setMethod(std::string requestMethod) {
	ft::toUpperString(requestMethod);
	for(_requestMethod = 0; _requestMethod < NUMBER_OF_METHODS; _requestMethod++) {
		if(requestMethod.compare(getMethodName()) == 0)
			return true;
	}
	return false;
}

bool ft::HttpRequest::setVersion(std::string protocolVersion) {
	ft::toUpperString(protocolVersion);
	for(_protocolVersion = 0; _protocolVersion < NUMBER_OF_VERSIONS; _protocolVersion++) {
		if(protocolVersion.compare(getVersionName()) == 0)
			return true;
	}
	return false;
}

void	ft::HttpRequest::setStatus(int status) {
	_status = status;
}

int 	ft::HttpRequest::getStatus() const {
	return _status;
}

int	ft::HttpRequest::setBadRequest(int status) {
	setStatus(status);
	_parsed = true;
	return status;
}

bool ft::HttpRequest::setPort(const std::string& port) {
	return ft::isNumber(port) && port.length() < 6 
		&& (_port = atoi(port.c_str())) > -1 && _port < 65536;
}

int ft::HttpRequest::getPort() const {
	return _port;
}

bool	ft::HttpRequest::setURI(const std::string& requestURI) {
	std::string::size_type	pos;
	
	if(requestURI.size() < 1)
		return false;
	if (requestURI[0] == '/') {									// relative path
		_relativePath = requestURI;
		return true;	
	} else if (requestURI.find("://") == std::string::npos) {
		return false;
	} else {													// absolute path
		_protocol = ft::getWithoutExtension(requestURI, "://");
		if (_protocol.compare(PROTOCOL))
			return false;
		std::string	tmpURI = getExtension(requestURI, "://");
		pos = tmpURI.find(":");
		if (pos != std::string::npos) {
			_serverName = ft::getWithoutExtension(tmpURI, "/");
			_relativePath = ft::getExtension(tmpURI, "/");
			_port = DEFAULT_PORT;
		} else {
			_serverName = ft::getWithoutExtension(tmpURI, ":");
			std::string::size_type end = tmpURI.find("/");			
			if (!setPort(tmpURI.substr(pos + 1, end - pos - 1)))
				return false;
			_relativePath = tmpURI.substr(end);
		}
	}
	return true;
}

const std::string&	ft::HttpRequest::getProtocol() const {
	return _protocol;
}


const std::string&	ft::HttpRequest::getServerName() const {
	return _serverName;
}

const std::string&	ft::HttpRequest::getRelativePath() const {
	return _relativePath;
}

bool	ft::HttpRequest::parseStartLine(const std::string& request) {
	std::vector<std::string> startLine = ft::split(request);
	if (startLine.size() < 3) {
    	setBadRequest(HttpResponse::BAD_REQUEST);
		return false;
	}
	if (!setVersion(startLine[2])) {
		setBadRequest(HttpResponse::HTTP_VERSION_NOT_SUPPORTED);
		return false;
	}
	if (!setMethod(startLine[0])) {
		setBadRequest(HttpResponse::METHOD_NOT_ALLOWED);
		return false;
	}
	if (startLine[1].length() > MAX_URI_LENGTH) {
		setBadRequest(HttpResponse::URI_TOO_LONG);
		return false;
	}
	ft::toLowerString(startLine[1]);
	if (!setURI(startLine[1])) {
		setBadRequest(HttpResponse::BAD_REQUEST);
		return false;
	}
	return true;
}


int	ft::HttpRequest::parse(const std::string& messages) {
	std::vector<std::string> segments = ft::split(messages, LINE_DOUBLE_END);
	if (segments.size() < 1)
    	return setBadRequest(HttpResponse::BAD_REQUEST);
	std::vector<std::string> headerLines = ft::split(segments[0], LINE_END);
	if (!parseStartLine(headerLines[0]))
		return _status;

	for (int i = 0; i < segments.size(); ++i)			// DELETE ME LATER!!! It's for testing!!!
		std::cout << segments[i];
	std::cout << "\n\n" << GREEN_COLOR << "PARSED DATA:\n" << "method: " << getMethodName()	// DELETE ME LATER!!!!!!!
				<< ", target: " << _requestURI << ", protocol version " << getVersionName()
				<< "\nPARSED URI:\n" << "protocol: " << getProtocol()
				<< ", server name: " << getServerName() << ", port: " << getPort()
				<< ", relative path: " << getRelativePath() << RESET_COLOR << std::endl;  
	return 0; 	// CHANGE ME LATER!!!!!!!
}




