#ifndef VIRTUAL_HOST_HPP
# define VIRTUAL_HOST_HPP

# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unordered_map>
# include <vector>
# include "HttpConstants.hpp"
# include "Location.hpp"
# include "utils.hpp"

namespace ft {
	class VirtualHost
	{
	public:
		VirtualHost();
		~VirtualHost();
		VirtualHost(const VirtualHost& other);

		VirtualHost&	operator=(const VirtualHost & other);

		void	setHost(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end);
		void	setPort(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end);
		void	setServerName(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end);

	private:
		in_addr_t										_host;
		int												_port;
		std::string										_serverName;
		std::string 									_root;
		unsigned long									_clientMaxBodySize;
		std::unordered_map<short, std::string>			_errorPages;
		std::unordered_map<std::string, ft::Location>	_locations;

		void	skipTokens(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end,
					size_t n, const char *neededToken = NULL);
	};
}
#endif