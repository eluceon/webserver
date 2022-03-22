#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

# include <string>
# include <vector>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fstream>
# include "utils.hpp"

namespace ft {
	class ConfigParser
	{
		public:
			ConfigParser(const std::string& configFile = "webserver.conf");
			~ConfigParser();
		private:
			std::string						_serverName;
			in_addr_t						_host;
			int								_port;
			unsigned long					_clientMaxBodySize;
			// std::map<short, std::string>	_errorPages;
			// std::map<std::string, Location> _locations;

			void	parse(const std::string& configFile);
			void	splitTokens(const std::string& configFile);
			void	splitTokens(const std::string& configFile,
						std::vector<std::string>& tokens);
	};
	
}
#endif