#include <string>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "utils.hpp"

ft::HttpRequest::HttpRequest()
	: _requestLine(""), _requestMethod(GET), _requestURI(""), _HTTPVersion(HTTP_1_1),
	_protocol("http"), _serverName(""), _relativePath(""), _queryString(""),
	_port(DEFAULT_PORT), _headers(), _body(), _parsed(false), _status(HTTP_OK),
	_chunked(false), _contentLength(0), _clientMaxBodySize(MAX_DEFAULT_BODY_SIZE)
{}

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

const std::string& ft::HttpRequest::getRequestLine() const {
	return _requestLine;
}

std::string ft::HttpRequest::getHTTPVersion() const {
	switch (_HTTPVersion)
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

void ft::HttpRequest::setMethod(std::string requestMethod) {
	ft::toUpperString(requestMethod);
	for(_requestMethod = 0; _requestMethod < NUMBER_OF_METHODS; _requestMethod++) {
		if(requestMethod.compare(getMethodName()) == 0)
			return;
	}
	throw HTTP_METHOD_NOT_ALLOWED;
}

void ft::HttpRequest::setHTTPVersion(std::string HTTPVersion) {
	ft::toUpperString(HTTPVersion);
	for(_HTTPVersion = 0; _HTTPVersion < NUMBER_OF_VERSIONS; _HTTPVersion++) {
		if(HTTPVersion.compare(getHTTPVersion()) == 0)
			return;
	}
	throw HTTP_VERSION_NOT_SUPPORTED;
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

void	ft::HttpRequest::setURI(const std::string& requestURI) {
	std::string::size_type	pos;
	
	if(requestURI.size() < 1)
		throw HTTP_BAD_REQUEST;
	if (requestURI[0] == '/') {									// relative path
		_relativePath = requestURI;
	} else if (requestURI.find("://") == std::string::npos) {
		throw HTTP_BAD_REQUEST;
	} else {													// absolute path
		_protocol = ft::getWithoutExtension(requestURI, "://");
		if (_protocol.compare(PROTOCOL))
			throw HTTP_BAD_REQUEST;
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
				throw HTTP_BAD_REQUEST;
			_relativePath = tmpURI.substr(end);
		}
	}
	if (_relativePath.find("?") != std::string::npos) {
		_queryString = ft::getExtension(_relativePath, "?");
		_relativePath = ft::getWithoutExtension(_relativePath, "?");
	}
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

const std::string&	ft::HttpRequest::getQueryString() const {
    return _queryString;
}

std::string ft::HttpRequest::getFullURL() const {
	return _protocol + "://" + _serverName + ":" + std::to_string(_port) + _relativePath + _queryString;
}

bool	ft::HttpRequest::isParsed() const {
    return _parsed;
}

const std::map<std::string, std::string>&	ft::HttpRequest::getHeaders() const {
    return _headers;
}

const std::string&	ft::HttpRequest::getBody() const {
	return _body;
}

unsigned long	ft::HttpRequest::getContentLength() const {
	return _contentLength;
}

void	ft::HttpRequest::parseRequestLine(const std::string& request) {
	std::vector<std::string> requestLine = ft::split(request);

	if (requestLine.size() < 3)
    	throw HTTP_BAD_REQUEST;
	setHTTPVersion(requestLine[2]);
	setMethod(requestLine[0]);
	if (requestLine[1].length() > MAX_URI_LENGTH)
		throw HTTP_URI_TOO_LONG;
	ft::toLowerString(requestLine[1]);
	setURI(requestLine[1]);
}

void	ft::HttpRequest::parseHeaders(const std::vector<std::string>& headerLines) {
	std::string::size_type pos;
	std::string headerName, headerValue;

	if (headerLines.size() > MAX_HEADER_FIELDS)
		throw HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE;
	for (size_t i = 1; i < headerLines.size(); ++i) {
		pos = 0;
		if (!ft::parseToken(headerLines[i], ":", pos, headerName, true, true, MAX_HEADER_NAME_LENGTH))
			throw HTTP_BAD_REQUEST;
		if (!ft::parseToken(headerLines[i], "\0", pos, headerValue, true, false, MAX_HEADER_VALUE_LENGTH))
			throw HTTP_BAD_REQUEST;
		ft::toLowerString(headerName);
		_headers.insert(std::make_pair(headerName, headerValue));
	}
}

void	ft::HttpRequest::processHeaders() {
	std::map<std::string, std::string>::const_iterator it;
	std::string::size_type	pos = 0;

	it = _headers.find("host");
	if (_serverName.empty() && it != _headers.end()) {
		ft::parseToken(it->second, ":", pos, _serverName, true);
		std::string strPort;
		ft::parseToken(it->second, "\0", pos, strPort, true);
		if (!strPort.empty() && !setPort(strPort))
			throw HTTP_BAD_REQUEST;
	} else if (_serverName.empty()) {							// server name not found
		throw HTTP_BAD_REQUEST;
	} else if (it == _headers.end()) {
		_headers.insert(std::pair<std::string, std::string>("host",
							_serverName + ":" + std::to_string(_port)));
	}

 	it = _headers.find("transfer-encoding");
 	if (it != _headers.end()) {
		_chunked = !it->second.compare("chunked");
	} else {
		it = _headers.find("content-length");
		if (it != _headers.end()) {
			_contentLength = std::strtoul(it->second.c_str(), nullptr, 10);
			if (errno == ERANGE || _contentLength > _clientMaxBodySize)
            	throw HTTP_PAYLOAD_TOO_LARGE;
		} else if (_requestMethod == POST || _requestMethod == PUT) {
			throw HTTP_LENGTH_REQUIRED;
		}
		_chunked = false;
	}
}

void	ft::HttpRequest::parseBody(const std::string& body) {
	
	std::cout << "Before\n";
	if (!_chunked) {
		std::cout << "NOT CHUNK\n";

		if (body.size() != _contentLength)
			throw HTTP_BAD_REQUEST;
		_body = body;
	} else {
		std::cout << "CHUNK\n";


		parseChunkedBody(body);
		_headers.erase(_headers.find("transfer-encoding"));
		_headers["content-length"] = std::to_string(_body.size());
		_contentLength = _body.length();
	}
}

void	ft::HttpRequest::parseChunkedBody(const std::string& body) {
	size_t		pos = 0;
	size_t		chunkSize = 0;
	size_t		bodyLen = body.length();
	std::string	chunkLen;

	while (pos < bodyLen) {
		if (body.find(CRLF, pos) == std::string::npos)
			throw HTTP_BAD_REQUEST;
		while (std::isspace(body[pos]))
			++pos;
		if (body.find("0\r\n", pos) == pos)
            return;
		while (std::isxdigit(body[pos]))
			chunkLen += body[pos++];
		if (body[pos] != ';' && body.find(CRLF, pos) != pos)
        	throw HTTP_BAD_REQUEST;
		chunkSize = std::strtoul(chunkLen.data(), NULL, 16);
		chunkLen.clear();
		if (chunkSize + _body.size() > _clientMaxBodySize)
			throw HTTP_BAD_REQUEST;
		pos = body.find(CRLF, pos) + 2;
		if (pos < bodyLen) {
			size_t end = chunkSize > bodyLen - pos ? bodyLen - pos : chunkSize;
			_body.append(body, pos, end); 
			pos += end;
			chunkSize -= end;
		}
	}
	throw HTTP_BAD_REQUEST;
}

int	ft::HttpRequest::parse(const std::string& messages) {
	std::vector<std::string> segments = ft::split(messages, CRLF_CRLF);
	if (segments.size() < 1)
    	return setBadRequest(HTTP_BAD_REQUEST);
	std::vector<std::string> headerLines = ft::split(segments[0], CRLF);
	_requestLine = headerLines[0];
	try {
		parseRequestLine(headerLines[0]);
		if (headerLines.size() > 1)
			parseHeaders(headerLines);
		processHeaders();
		if (segments.size() == 2 && (_chunked || _contentLength > 0))
        	parseBody(segments[1]);
	} catch (int statusCode) {
		return setBadRequest(statusCode);			// DELETE return LATER 
		// setBadRequest(statusCode);
	}
	_parsed = true;


	for (int i = 0; i < segments.size(); ++i)			// DELETE ME LATER!!! It's for testing!!!
		std::cout << segments[i];
	
	std::cout << "\n\n" << GREEN_COLOR << "PARSED DATA:\n" << "method: " << getMethodName()	// DELETE ME LATER!!!!!!!
				<< ", target: " << _requestURI << ", HTTP version " << getHTTPVersion()
				<< "\nPARSED URI:\n" << "protocol: " << getProtocol()
				<< ", server name: " << getServerName() << ", port: " << getPort()
				<< ", relative path: " << getRelativePath() 
				<< ", query string: " << getQueryString() 
				<< "\nfull uri: " << getFullURL()
				<< "\ncontent-Length: " << getContentLength()
				<< "\nChunked: " << _chunked
				<< "\nParsed: " << isParsed() << ", response status: " << getStatus() << RESET_COLOR << std::endl;
	
	std::map<std::string, std::string> tmpHeaders = getHeaders();
	std::map<std::string, std::string>::const_iterator it = tmpHeaders.begin();
	std::cout << "HEADERS:\n";
	for (; it != tmpHeaders.end(); ++it) {
		std::cout << it->first << ": " << it->second << '\n';
	}
	std::cout << "BODY:\n";
		std::cout << _body << std::endl;
	return _status; 	// CHANGE ME LATER!!!!!!!
}

