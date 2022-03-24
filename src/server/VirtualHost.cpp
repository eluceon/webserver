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
		&& (_port = std::stoi(*it)) < 1 || _port > 65535)
		ft::errorExit("Invalid port in config file");
	skipTokens(it, end, 1, ";");
}

void	ft::VirtualHost::setServerName(std::vector<std::string>::const_iterator &it,
			std::vector<std::string>::const_iterator &end) {
	skipTokens(it, end, 1);
	_serverName = *it;
	skipTokens(it, end, 1, ";");
}

void	ft::VirtualHost::setRoot(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end) {
	skipTokens(it, end, 1);
	_root = *it;
	skipTokens(it, end, 1, ";");
	
}

void	ft::VirtualHost::setClientMaxBodySize(std::vector<std::string>::const_iterator &it,
			std::vector<std::string>::const_iterator &end) {
	skipTokens(it, end, 1);
	if (!ft::isNumber(*it))
		ft::errorExit("Invalid format of client_max_body_size in config file");
	else if (it->length() > 3
		|| (_clientMaxBodySize = std::stoul(*it) * 1048576) > MAXIMUM_MAX_BODY_SIZE) {
		ft::errorExit("client_max_body_size in config file exceeds the maximum value");
	}
	skipTokens(it, end, 1, ";");
}

void	ft::VirtualHost::setErrorPage(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end) {
	int 		error_code;
	struct stat statbuf;

	skipTokens(it, end, 1);
	if (!(ft::isNumber(*it)) || it->length() > 3
		|| (error_code = std::stoi(*it)) < 100 || error_code > 599)
	{
		ft::errorExit("Invalid format of error code in config file");
	}
	skipTokens(it, end, 1);
    if (stat((*it).data(), &statbuf) < 0)
		ft::systemErrorExit("can't open error_page " 
			+ std::to_string(error_code) + " in config file" );
	if (!S_ISREG(statbuf.st_mode))
		ft::errorExit("error_page :" + std::to_string(error_code) 
			+ "in config file is not a file");
	_errorPages.insert(std::make_pair(error_code, *it));
	skipTokens(it, end, 1, ";");
}