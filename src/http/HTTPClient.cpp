#include "HTTPClient.hpp"

ft::HTTPClient::HTTPClient(int fd)
	: _httpRequest(NULL),
	_fd(fd)
{}

ft::HTTPClient::HTTPClient(const ft::HTTPClient &other)
	: _httpRequest(other._httpRequest),
	_fd(other._fd)
{}

ft::HTTPClient::~HTTPClient() {
	if (_httpRequest) {
		delete _httpRequest;
		_httpRequest = NULL;
	}
}

ft::HTTPClient &ft::HTTPClient::operator=(const ft::HTTPClient &other) {
	if (this != &other) {
		_httpRequest = other._httpRequest;
		_fd = other._fd;
	}
	return *this;
}

void	ft::HTTPClient::parse(const char *buf) {
	if (!_httpRequest)
		_httpRequest = new HTTPRequest();
	_httpRequest->parse(buf);
}

void	ft::HTTPClient::response(
		std::unordered_map<std::string, ft::VirtualHost>& virtualHosts
	)
{
	if (!_httpRequest)
		ft::errorExit("HTTPRequest is needed for HTTPResponse class");
	HTTPResponse *httpResponse = new HTTPResponse(_httpRequest, virtualHosts);
	std::string response = httpResponse->getResponse();
	send(_fd, response.c_str(), response.size(), 0);
	delete httpResponse;
}

const ft::HTTPRequest	*ft::HTTPClient::getHttpRequest() const {
	return _httpRequest;
}

int ft::HTTPClient::getFd() const {
	return _fd;
}