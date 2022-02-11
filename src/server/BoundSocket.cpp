#include "BoundSocket.hpp"

ft::BoundSocket::BoundSocket() {
	setServerAddressStructure();
	bindAddressToSocket();
}

ft::BoundSocket::~BoundSocket() {}

void	ft::BoundSocket::bindAddressToSocket() {
	if (bind(_socket, (struct sockaddr *)&_servAddr, sizeof(_servAddr)) < 0)
		ft::systemErrorExit("bind error");
}

void ft::BoundSocket::setServerAddressStructure() {
   	std::fill_n((char *)&_servAddr, sizeof(_servAddr), '\0');
	_servAddr.sin_family = AF_INET;
	_servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	_servAddr.sin_port = htons(SERV_PORT);
}