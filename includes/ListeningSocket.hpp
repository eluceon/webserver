#ifndef LISTENING_SOCKET_HPP
# define LISTENING_SOCKET_HPP

# include <stdlib.h>
# include "BoundSocket.hpp"

namespace ft
{
	class ListeningSocket : public BoundSocket {
		public:
			ListeningSocket();
			ListeningSocket(const ListeningSocket& other);
			virtual ~ListeningSocket();

			ListeningSocket &operator=(const ListeningSocket& other);

		private:
			int	_listeningSocket;

			void    startListening();
	};
}
#endif