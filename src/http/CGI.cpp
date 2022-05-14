#include "../../includes/CGI.hpp"

namespace ft {
	CGI::CGI() {}
	CGI::CGI(std::string &res, std::string &res_path, HTTPRequest* req) :
	_res(res), _res_path(res_path), _req(req) {}
	CGI::CGI(const CGI &x) { *this = x; }
	CGI::~CGI() {}

	CGI &CGI::operator=(const CGI &x) {
		if (this != &x) {
			this->_res = x._res;
			this->_res_path = x._res_path;
		}
		return *this;
	}

	std::string CGI::execCGI() {
		int res;
		char **argv;
		char *file = const_cast<char *>(_res.c_str());
		int fd;
		int fds[2];

		if (!(argv = (char **)malloc(sizeof(char *) * 3)))
			return "";
		argv[0] = file;
		argv[1] = const_cast<char *>(_res_path.c_str());
		argv[2] = NULL;
		if (pipe(fds) == -1) {
			std::cout << "Pipe failed\n";
			throw ;
		}
		if (!fork()) {
			close(fds[1]);
			dup2(fds[0], 0);
			fd = open("./www/cgi", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			if (fd < 0) {
				std::cout << "Failed to create file\n";
				throw ;
			}
			dup2(fd, 1);
			dup2(fd, 2);
			res = execve(file, argv, NULL);
			close(STDIN_FILENO);
			close(fd);
			close(fds[0]);
			exit(0);
		}
		close(fds[0]);
		write(fds[1], _req->getBody().c_str(), _req->getContentLength());
		close(fds[1]);
		wait(&res);
		return (readFile("./www/cgi"));
	}
}


