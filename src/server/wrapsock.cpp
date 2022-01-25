#include "Server.hpp"

namespace ft
{
	int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr) {
		int		n;

	again:
		if ( (n = accept(fd, sa, salenptr)) < 0) {
	#ifdef	EPROTO
			if (errno == EPROTO || errno == ECONNABORTED)
	#else
			if (errno == ECONNABORTED)
	#endif
				goto again;
			else
				ft::systemErrorExit("accept error");
		}
		return(n);
	}
} // namespace name
