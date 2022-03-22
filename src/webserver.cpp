#include "Server.hpp"

int main() {
	const std::string configFile = "webserver.conf";
	ft::ConfigParser	config(configFile);
	ft::Server::getInstance(configFile);
    return 0;
}