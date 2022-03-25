#include "Location.hpp"

ft::Location::Location() {}
ft::Location::~Location() {}


ft::Location::Location(const Location & other)
	: _root(other._root), _methods(other._methods),
	_autoindex(other._autoindex), _index(other._index),
	_fastcgiPass(other._fastcgiPass), _maxBodySize(other._maxBodySize)
{}

ft::Location&	ft::Location::operator=(const Location & other) {
	if (this != &other) {
		_root = other._root;
		_methods = other._methods;
		_autoindex = other._autoindex;
		_index = other._index;
		_fastcgiPass = other._fastcgiPass;
		_maxBodySize = other._maxBodySize;

	}
	return *this;
}

void	ft::Location::parseLocation(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end, const char *curDir) {
	_root = curDir;
	skipTokens(it, end, 1);
	std::string	path = *it;
	skipTokens(it, end, 1, "{");
	skipTokens(it, end, 1);

	while (it != end && *it != "}") {
		if (*it == "root") {

		} else if (*it == "methods") {

		} else if (*it == "autoindex") {

		} else if (*it == "return") {

		} else if (*it == "index") {

		} else if (*it == "client_max_body_size") {

		} if (!path.compare(0, 2, "0.") && *it == "fastcgi_pass") {
		
		}
	}
	if (it == end)
		ft::errorExit("Invalid config file");
}