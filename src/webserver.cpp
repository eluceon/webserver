#include "Server.hpp"

int main() {
	const std::string configFile = "webserver.conf";
	ft::Config	config(configFile);

	ft::Server::getInstance(config.getVirtualHosts());

    return 0;
}