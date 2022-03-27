#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

# include <string>
# include <vector>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fstream>
# include "utils.hpp"
# include <unordered_map>
# include "VirtualHost.hpp"

namespace ft {
	class ConfigParser
	{
		public:
			ConfigParser(const std::string &configFile = "webserver.conf");
			ConfigParser(const ConfigParser &);
			~ConfigParser();

			ConfigParser &operator=(const ConfigParser &other);

		private:
			std::vector<ft::VirtualHost>	_virtualHosts;

			void	parse(const std::string& configFile);
			void	splitTokens(const std::string& configFile);
			void	splitTokens(const std::string& configFile,
						std::vector<std::string>& tokens);
			void	validateParentheses(const std::vector<std::string> &tokens,
						const std::string &openParenthesis,
						const std::string &closingParenthesis);
			void	hasMinimumParameters(const ft::VirtualHost &virtualHost);
	};
	
}
#endif