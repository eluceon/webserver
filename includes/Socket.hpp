#ifndef SOCKET_HPP
# define SOCKET_HPP

# include	<sys/types.h>	/* basic system data types */
# include	<sys/socket.h>	/* basic socket definitions */
# include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
# include	<arpa/inet.h>	/* inet(3) functions */
# include	<string>

# define	SERV_PORT	8080

# include "utils.hpp"
	
namespace ft
{
	class Socket {
		public:
			Socket();
			Socket(const Socket& other);

			Socket& operator=(const Socket& other);

			virtual ~Socket();

			int	getSocket();

		protected:
			int					_socket;
			// _servAddr is a structure specifies a transport address
			// and port for the AF_INET address family
			struct sockaddr_in	_servAddr;

			void	createSocket();
			void	setServerAddressStructure();
	};	
}


#endif