#include "Server.hpp"
#include "HttpRequest.hpp"

ft::Server::Server(const std::string& configFile) {
	registerSignals();
	// parseConfig(configFile);
	timestamp("Starting up..");
	_listeningSocket = new ft::ListeningSocket();
	initialize();
	run();
}

ft::Server::~Server() {
	delete _listeningSocket;
}

ft::Server&	ft::Server::getInstance(const std::string& configFile) {
	static Server singleton(configFile);
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
	int					maxIdx = 0;		// max index into _client[] array
	
	while(true) {
		if ( (countReadyFd = poll(_client, maxIdx + 1, INFTIM)) < 0)
			systemErrorExit("poll error");
		if (_client[0].revents & POLLRDNORM) {	// new client connection
			clilen = sizeof(cliaddr);
			connfd = Accept(_listeningSocket->getSocket(), (struct sockaddr *) &cliaddr, &clilen);
#ifdef	NOTIFICATIONS
			std::cout << GREEN_COLOR << "New client: "
				<< sockNtop((struct sockaddr *) &cliaddr, clilen) << RESET_COLOR << std::endl;
#endif
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
		checkConnectionsForData(maxIdx, countReadyFd);
	}
}

void	ft::Server::checkConnectionsForData(int	maxIdx, int countReadyFd) {
	int		sockfd;
	ssize_t	n;
	char	buf[MAXLINE];

	for (int i = 1; i <= maxIdx; i++) {		// check all clients for data
		if ( (sockfd = _client[i].fd) < 0)
			continue;
		if (_client[i].revents & (POLLRDNORM | POLLERR)) {
			std::fill_n(buf, sizeof(char) * MAXLINE, '\0');
			if ( (n = read(sockfd, buf, MAXLINE)) < 0) {
				if (errno == ECONNRESET) {	// connection reset by client
#ifdef	NOTIFICATIONS
					std::cout << RED_COLOR << "_client[" << i << "] aborted connection" << RESET_COLOR << std::endl;
#endif
					if (close(sockfd) == -1)
						systemErrorExit("close error");
					_client[i].fd = -1;
				} else
					systemErrorExit("read error");
			} else if (n == 0) {			// connection closed by client
#ifdef	NOTIFICATIONS
				std::cout << RED_COLOR << "_client[" << i << "] closed connection" << RESET_COLOR << std::endl;
#endif
				if (close(sockfd) == -1)
					systemErrorExit("close error");
				_client[i].fd = -1;
			} else {
				// std::cout << buf << std::endl;		// print message from client
				HttpRequest *httpRequest = new HttpRequest();
				int tmp;
				if ((tmp = httpRequest->parse(buf)) != 0)		//DELETE ME LATER
					std::cout << "\nRESPONSE STATUS CODE: " << tmp << '\n';
				// std::string logBuffer = "From " + sockNtop((struct sockaddr *) &cliaddr, &clilen);
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
* This function writes a timestamp string to the open fileLog 
*/ 
void ft::Server::timestamp(const std::string& msg) {
	std::fstream	fout("./logs/webserver.log", std::ios_base::out | std::ios_base::app);

	if ((fout.rdstate() & std::ifstream::failbit) != 0 )
	    std::cerr << "Error opening 'webserver.log'" << std::endl;
	else {
		std::time_t timer = time(&timer);
		fout << std::put_time(std::localtime(&timer), "%d/%m/%Y %H:%M:%S> ")
				<< msg << '\n';
	}
	if ((fout.rdstate() & std::ifstream::badbit) != 0 ) {
		std::cerr << "Writing 'webserver.log' error" << std::endl;
	}
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
