#include "Server.hpp"

int main() {
	const std::string configFile = "webserver.conf";

	ft::Server::getInstance(configFile);
    return 0;
}