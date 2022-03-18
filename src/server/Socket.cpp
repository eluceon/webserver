#include "Socket.hpp"

ft::Socket::Socket() {
	createSocket();
}

ft::Socket::~Socket() {}

int	ft::Socket::getSocket() {
	return _socket;
}

void ft::Socket::createSocket() {
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket < 0)
		ft::systemErrorExit("socket error");
	int yes = 1;
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
    	ft::systemErrorExit("setting socket option SO_REUSEADDR"); 
}
