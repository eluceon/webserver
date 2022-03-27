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
	class Config
	{
		public:
			Config(const std::string &configFile = "webserver.conf");
			Config(const Config &);
			~Config();

			Config &operator=(const Config &other);

			const std::vector<ft::VirtualHost> &getVirtualHosts() const;

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