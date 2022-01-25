#include "ListeningSocket.hpp"

ft::ListeningSocket::ListeningSocket() {
	startListening();
}

ft::ListeningSocket::~ListeningSocket(){}

void	ft::ListeningSocket::startListening() {
	char	*ptr;
	int		backlog;

	/* Can override 2nd argument with environment variable */
	if ( (ptr = std::getenv("LISTENQ")) != NULL)
		backlog = std::atoi(ptr);
	else
		backlog = SOMAXCONN;

	if (listen(_socket, backlog) < 0)
		ft::systemErrorExit("listen error");
}

