#include "BoundSocket.hpp"

ft::BoundSocket::BoundSocket() {
	bindAddressToSocket();
}

ft::BoundSocket::~BoundSocket() {}

void	ft::BoundSocket::bindAddressToSocket() {
	if (bind(_socket, (struct sockaddr *)&_servAddr, sizeof(_servAddr)) < 0)
		ft::systemErrorExit("bind error");
}