#ifndef VIRTUAL_HOST_HPP
# define VIRTUAL_HOST_HPP

# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unordered_map>
# include <vector>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
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
		void	setRoot(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end);
		void	setClientMaxBodySize(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end);
		void	setErrorPage(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end, const char *curDir);
		void	setLocation(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end, const char *curDir);
		
		in_addr_t	getHost() const; 
		int	getPort() const;
		const std::string &getServerName() const;
		unsigned long	getClientMaxBodySize() const;
		const std::unordered_map<short, std::string> &getErrorPages() const;
		const std::unordered_map<std::string, ft::Location> &getLocations() const;

	private:
		in_addr_t										_host;
		int												_port;
		std::string										_serverName;
		unsigned long									_clientMaxBodySize;
		std::unordered_map<short, std::string>			_errorPages;
		std::unordered_map<std::string, ft::Location>	_locations;
	};
}
#endif