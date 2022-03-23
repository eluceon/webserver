#include "VirtualHost.hpp"
ft::VirtualHost::VirtualHost() {}
ft::VirtualHost::~VirtualHost() {}

void	ft::VirtualHost::skipTokens(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end,
					size_t n, const char *neededToken) {
	while (it != end && n-- > 0)
		++it;
	if (it == end || (neededToken && it->compare(neededToken)))
		ft::errorExit("Invalid config file");
}

void	ft::VirtualHost::setHost(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end) {
	skipTokens(it, end, 1);
	_host = inet_addr(it->data());
	if (_host == INADDR_NONE)
		ft::errorExit("Invalid host in config file");
	skipTokens(it, end, 1, ";");
}

void	ft::VirtualHost::setPort(std::vector<std::string>::const_iterator &it,
					 std::vector<std::string>::const_iterator &end) {
	skipTokens(it, end, 1);
	if (!ft::isNumber(*it) || it->length() > 6 
		&& (_port = atoi(it->c_str())) < 1 || _port > 65535)
		ft::errorExit("Invalid port in config file");
	skipTokens(it, end, 1, ";");
}

void	ft::VirtualHost::setServerName(std::vector<std::string>::const_iterator &it,
			std::vector<std::string>::const_iterator &end) {
	skipTokens(it, end, 1);
	_serverName = *it;
	skipTokens(it, end, 1, ";");
}