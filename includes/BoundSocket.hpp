#ifndef BOUND_SOCKET_HPP
# define BOUND_SOCKET_HPP

#include "Socket.hpp"

namespace ft
{
	class BoundSocket : public Socket
	{
		public:
			BoundSocket();
			BoundSocket(const BoundSocket& other);

			BoundSocket& operator=(const BoundSocket& other);
			
			virtual ~BoundSocket();

		private:
			void	bindAddressToSocket();
	};
		
}


#endif