#include "CGI.hpp"

ft::CGI::CGI(void) : _method(""), _query_string("") {}

ft::CGI::CGI(HttpRequest &rec) : _method(rec.getMethodName()), _query_string(rec.getQueryString()) {}

ft::CGI::CGI(const CGI &x) {
	if (this != &x) {
		*this = x;
	}
}

ft::CGI	&ft::CGI::operator=(const CGI &x) {
	if (this != &x) {
		_method = x._method;
		_query_string = x._query_string;
	}
	return *this;
}

ft::CGI::~CGI(void) {
	UnsetEnv();
}

void	ft::CGI::SetEnv(HttpRequest &rec) {
	setenv("REQUEST_METHOD", rec.getMethodName().c_str(), 1);
	setenv("QUERY_STRING", rec.getQueryString().c_str(), 1);
	setenv("CONTENT_LENGTH", std::to_string(rec.getContentLength()).c_str(), 1);
}

void	ft::CGI::UnsetEnv(void) {
	unsetenv("REQUEST_METHOD");
	unsetenv("QUERY_STRING");
	unsetenv("CONTENT_LENGTH");
}

std::string ft::CGI::getContent(void) {
	if (!_method.compare("GET"))
		parseStrGet();
	else if (!_method.compare("POST")) {
		parseStrPost();
		setLen();
		if (_content_length > 0)
			readLenBytes();
		else
			throw ft::CGI::LengthException();
	}
}

char ft::CGI::toUpper(char c) {
	if ((c >= 'a') && (c <= 'z')) {
		return 'A' + (c - 'a');
	}
	else
		return c;
}
char ft::CGI::toDec(char c) {
	c = toUpper(c);
	if ((c >= '0') && (c <= '9')) { return c - '0'; }
	if ((c >= 'A') && (c <= 'F')) { return c - 'A' + 10; }
}

char *ft::CGI::getParameter(char *buffer, char *name) {
	if (buffer == NULL) { return NULL; }

	char	*pos;
	u_long	length = 512, i = 0, j = 0;
	char	h1, h2, Hex;

	char	*p;
	p = (char *)malloc(length);
	if (p == NULL) { return NULL; }

	pos = strstr(buffer, name);
	if (pos == NULL) { return NULL; }

	if ((pos != buffer) && (*(pos - 1) != '&')) { return NULL; }

	pos += strlen(name);

	while ((*(pos + i) != '&') && (*(pos + i) != '\0')) {
		if (*(pos + i) == '%') {
			i++;
			h1 = toDec(*(pos + i));
			i++;
			h2 = toDec(*(pos + i));
			h1 = h1 << 4;
			*(p + j) = h1 + h2;
		}
		else {
			if (*(pos + i) != '+')
				*(p + j) = *(pos + i);
			else
				*(p + j) = ' ';
		}
		i++;
		j++;
		if (j >= length) {
			p = (char *)realloc(p, length + 20);
			length += 20;
		}
		if (j < length) {
			p = (char *)realloc(p, j + 1);
		}
		return p;
	}
}

void	ft::CGI::parseStrGet(void) {}

void	ft::CGI::parseStrPost(void) {}

void	ft::CGI::setLen() { _content_length = std::atol(getenv("CONTENT_LENGTH")); }

std::string	ft::CGI::readLenBytes(void) {
	char	*cgi_data;

	cgi_data = (char*)malloc(_content_length);
	if (cgi_data != NULL)
		read(_content_length, cgi_data, STDIN_FILENO);
	else {
		throw ft::CGI::AllocException();
	}
}



const char *ft::CGI::LengthException::what() const throw() {
	return "Content length is zero";
}

const char *ft::CGI::AllocException::what() const throw() {
	return "Allocation failed";
}
