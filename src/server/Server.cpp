#include "Server.hpp"
#include "HttpRequest.hpp"

ft::Server::Server() {
	_listeningSocket = new ft::ListeningSocket();
	initialize();
	run();
}

ft::Server::~Server() {
	delete _listeningSocket;
}

ft::Server&	ft::Server::getInstance() {
	static Server singleton;
    return singleton;
}

void	ft::Server::initialize() {
	client[0].fd = _listeningSocket->getSocket();
	client[0].events = POLLRDNORM;
	for (int i = 1; i < OPEN_MAX; i++)
		client[i].fd = -1;		// -1 indicates available entry
}

void	ft::Server::run() {
	int					countReadyFd;	// count of ready descriptors
	int					i, connfd;
	struct sockaddr_in	cliaddr;
	socklen_t			clilen;
	int					maxIdx = 0;		// max index into client[] array
	
	while(true) {
		if ( (countReadyFd = poll(client, maxIdx + 1, INFTIM)) < 0)
			systemErrorExit("poll error");
		if (client[0].revents & POLLRDNORM) {	// new client connection
			clilen = sizeof(cliaddr);
			connfd = Accept(_listeningSocket->getSocket(), (struct sockaddr *) &cliaddr, &clilen);
#ifdef	NOTIFICATIONS
			std::cout << GREEN_COLOR << "New client" << RESET_COLOR << std::endl;
#endif
			for (i = 1; i < OPEN_MAX; i++)
				if (client[i].fd < 0) {
					client[i].fd = connfd;	// save descriptor
					break;
				}
			if (i == OPEN_MAX)
				errorExit("too many clients");

			client[i].events = POLLRDNORM;
			if (i > maxIdx)
				maxIdx = i;

			if (--countReadyFd <= 0)
				continue;					// no more readable descriptors
		}
		checkConnectionsForData(maxIdx, countReadyFd);
	}
}

void	ft::Server::checkConnectionsForData(int	maxIdx, int countReadyFd) {
	int		sockfd;
	ssize_t	n;
	char	buf[MAXLINE];

	for (int i = 1; i <= maxIdx; i++) {		// check all clients for data
		if ( (sockfd = client[i].fd) < 0)
			continue;
		if (client[i].revents & (POLLRDNORM | POLLERR)) {
			if ( (n = read(sockfd, buf, MAXLINE)) < 0) {
				if (errno == ECONNRESET) {	// connection reset by client
#ifdef	NOTIFICATIONS
					std::cout << RED_COLOR << "client[" << i << "] aborted connection" << RESET_COLOR << std::endl;
#endif
					if (close(sockfd) == -1)
						systemErrorExit("close error");
					client[i].fd = -1;
				} else
					systemErrorExit("read error");
			} else if (n == 0) {			// connection closed by client
#ifdef	NOTIFICATIONS
				std::cout << RED_COLOR << "client[" << i << "] closed connection" << RESET_COLOR << std::endl;
#endif
				if (close(sockfd) == -1)
					systemErrorExit("close error");
				client[i].fd = -1;
			} else {
				std::cout << buf << std::endl;		// print message from client
				// HttpRequest *httpRequest = new HttpRequest();
				// httpRequest->parse(buf);
				// delete httpRequest;
			}
			if (--countReadyFd <= 0)
				break;						// no more readable descriptors
		}
	}

}
