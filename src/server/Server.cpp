#include "Server.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"


ft::Server::Server(const std::vector<ft::VirtualHost> &virtualHosts) {
	registerSignals();
	timestamp("Starting up..");
	_listeningSocket = new ft::ListeningSocket();
	initialize();
	run();
}

ft::Server::~Server() {
	delete _listeningSocket;
}

ft::Server&	ft::Server::getInstance(const std::vector<ft::VirtualHost> &virtualHosts) {
	static Server singleton(virtualHosts);
    return singleton;
}

void	ft::Server::initialize() {
	_client[0].fd = _listeningSocket->getSocket();
	_client[0].events = POLLRDNORM;
	for (int i = 1; i < OPEN_MAX; i++)
		_client[i].fd = -1;		// -1 indicates available entry
}

void	ft::Server::run() {
	int					countReadyFd;	// count of ready descriptors
	int					i, connfd;
	struct sockaddr_in	cliaddr;
	socklen_t			clilen;
	nfds_t				maxIdx = 0;		// max index into _client[] array
	
	while(true) {
		if ( (countReadyFd = poll(_client, maxIdx + 1, INFTIM)) < 0)
			systemErrorExit("poll error");
		if (_client[0].revents & POLLRDNORM) {	// new client connection
			clilen = sizeof(cliaddr);
			connfd = Accept(_listeningSocket->getSocket(), (struct sockaddr *) &cliaddr, &clilen);
			fcntl(connfd, F_SETFL, O_NONBLOCK);
			timestamp("New client: " + sockNtop((struct sockaddr *) &cliaddr, clilen));
			for (i = 1; i < OPEN_MAX; i++)
				if (_client[i].fd < 0) {
					_client[i].fd = connfd;	// save descriptor
					break;
				}
			if (i == OPEN_MAX)
				errorExit("too many clients");

			_client[i].events = POLLRDNORM;
			if (i > maxIdx)
				maxIdx = i;
			if (--countReadyFd <= 0)
				continue;					// no more readable descriptors
		}
		checkConnectionsForData(maxIdx, countReadyFd, &cliaddr, clilen);
	}
}

ssize_t	ft::Server::readn(int fd, std::string& buffer) {
	ssize_t	nread;
	char	buf[MAXLINE + 1];

	while((nread = recv(fd, buf, MAXLINE, 0)) > 0) {
		buf[MAXLINE] = '\0';
		buffer.append(buf);
	}
	return nread == 0 ? buffer.size() : nread;
}

void	ft::Server::checkConnectionsForData(int	maxIdx, int countReadyFd,
						struct sockaddr_in	*cliaddr, socklen_t	clilen) {
	int		sockfd;
	ssize_t	n;
	std::string	buffer;

	for (int i = 1; i <= maxIdx; i++) {		// check all clients for data
		if ( (sockfd = _client[i].fd) < 0)
			continue;
		if (_client[i].revents & (POLLRDNORM | POLLERR)) {
			if ( (n = readn(sockfd, buffer)) < 0 && errno != EWOULDBLOCK) {
				if (errno == ECONNRESET) {	// connection reset by client
					timestamp("_client[" + std::to_string(i) +"] aborted connection");
					if (close(sockfd) == -1)
						systemErrorExit("close error");
					_client[i].fd = -1;
				} else
					systemErrorExit("read error");
			} else if (n == 0) {			// connection closed by client
				timestamp("_client[" + std::to_string(i) +"] closed connection");
				if (close(sockfd) == -1)
					systemErrorExit("close error");
				_client[i].fd = -1;
			} else {
				HttpRequest *httpRequest = new HttpRequest();		
				httpRequest->parse(buffer);
				if (!httpRequest->isParsed()) {
					delete httpRequest;
					continue;
				}
				HttpResponse *httpResponse = new HttpResponse(httpRequest);
				std::string response = httpResponse->getResponse();
				send(sockfd, response.c_str(), response.size(), 0);
				delete httpResponse;
				delete httpRequest;
			}
			if (--countReadyFd <= 0)
				break;						// no more readable descriptors
		}
	}
}

void ft::Server::handleShutdown(int signal) {
	timestamp("Shutting down on signal " + std::to_string(signal));
    exit(signal);
}

void	ft::Server::registerSignals() {
	signal(SIGTERM, ft::Server::handleShutdown);   // call handleShutdown when killed
   	signal(SIGINT, ft::Server::handleShutdown);   // call handleShutdown when interrupted
}

/*
* The function sockNtop takes a pointer to a socket address structure,
* looks inside the structure, return the string presentation
* of socket address (ip_address:port)
*/
std::string	ft::Server::sockNtop(const struct sockaddr *sa, socklen_t salen) {
    char		str[INET6_ADDRSTRLEN];		// IP6 is larger then IP4
	std::string	socket;

	switch (sa->sa_family) {
		case AF_INET: {
			struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

			if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
				socket = "not_nown_IP";
			else
				socket = std::string(str) + ':' + std::to_string(ntohs(sin->sin_port));
			break;
		}
		case AF_INET6: {
			struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;

			if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
				socket = "not_nown_IP";
			else 
				socket = '[' + std::string(str) + "]:" + std::to_string(ntohs(sin6->sin6_port));
		}
	}
	return socket;
}
