#include "Socket.hpp"

ft::Socket::Socket() {
	createSocket();
	setServerAddressStructure();
}

ft::Socket::~Socket() {}

int	ft::Socket::getSocket() {
	return _socket;
}

void ft::Socket::createSocket() {
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket < 0)
		ft::systemErrorExit("socket error");
}

void ft::Socket::setServerAddressStructure() {
   	std::fill_n((char *)&_servAddr, sizeof(_servAddr), '\0');
	_servAddr.sin_family = AF_INET;
	_servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	_servAddr.sin_port = htons(SERV_PORT);
}
