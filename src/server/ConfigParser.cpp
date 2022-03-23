#include "ConfigParser.hpp"

ft::ConfigParser::ConfigParser(const std::string& configFile) {
	parse(configFile);
}

ft::ConfigParser::~ConfigParser() {}

void ft::ConfigParser::splitTokens(const std::string& configFile,
		std::vector<std::string>& tokens) {

    std::fstream	fin(configFile, std::ios::in | std::ios::binary);
    std::string		line;
	std::string 	token;

	if ((fin.rdstate() & std::ios::failbit) != 0)
        ft::errorExit("Error opening " + configFile);
	while (std::getline(fin, line)) {
		token.clear();
		size_t len = line.size();
		for (int i = 0; i < len; ++i) {
			if (line[i] != ';' && line[i] != '#' && !std::isspace(line[i])) {
				token += line[i];
				continue;
			}
			if (!token.empty()) {
				tokens.push_back(token);
				token.clear();
			}
			if (line[i] == ';')
				tokens.push_back(std::string(1, line[i]));
			else if (line[i] == '#')
				break;
		}
		if (!token.empty())
			tokens.push_back(std::string(token));
	}
    fin.close();
}

void ft::ConfigParser::parse(const std::string& configFile) {
	std::vector<std::string>	tokens;

    splitTokens(configFile, tokens);
// 	for (int i = 0; i < tokens.size(); ++i) {
// 		std::cout << tokens[i] << '\n'
// ;	}

	size_t size = tokens.size();
	std::vector<std::string>::const_iterator it = tokens.cbegin();
	std::vector<std::string>::const_iterator end = tokens.cend();
    for ( ; it < end; ++it) // parsing servers
    {
        if (*it != "server" && *(++it) != "{")
            ft::errorExit("Invalid config file");
        ft::VirtualHost virtualHost;
        std::vector<std::string>::iterator check;
        while (++it < end && *it != "}") // parsing inside server
        {
            if (*it == "host") {
				virtualHost.setHost(it, end);
            } else if (*it == "port") {
				virtualHost.setPort(it, end);
            } else if (*it == "server_name") {
				virtualHost.setServerName(it, end);
            } else if (*it == "error_page") {
            } else if (*it == "client_max_body_size") {
            } else if (*it == "location") {
            }
        }
        // add(server);
    }
}