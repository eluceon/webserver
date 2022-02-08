#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <unistd.h>
# include <errno.h>
# include <poll.h>
# include "ListeningSocket.hpp"

/* 
** POSIX requires that an #include of <poll.h> define INFTIM, but many
** systems still define it in <sys/stropts.h>.  We don't want to include
** all the STREAMS stuff if it's not needed, so we just define INFTIM here.
** This is the standard value, but there's no guarantee it is -1. 
*/

# ifndef INFTIM
#  define INFTIM	(-1)    // infinite poll timeout
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX	10240	// max open files per process
# endif

#define	MAXLINE		4096	// max text line length


/* Define for notifications*/
# define NOTIFICATIONS 1

namespace ft
{
	class Server
	{
	public:
		static Server&	getInstance();

	private:
		Server();
		Server(const Server& other);
		virtual ~Server();
		
		Server&	operator=(const Server & other);

		ft::ListeningSocket	*_listeningSocket;
		struct pollfd		client[OPEN_MAX];

		void	initialize();
		void	run();
		void	checkConnectionsForData(int	maxIdx, int countReadyFd);
	};
} // namespace ft

#endif
