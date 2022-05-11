#include "../../includes/CGI.hpp"

extern char **environ;

namespace ft {
	CGI::CGI() {}
	CGI::CGI(std::string &res, std::string &res_path, std::map<std::string, std::string> &headers, HTTPRequest* req) :
	_res(res), _res_path(res_path), _headers(headers), _req(req) {}
	CGI::CGI(const CGI &x) { *this = x; }

	CGI &CGI::operator=(const CGI &x) {
		if (this != &x) {
			this->_res = x._res;
			this->_res_path = x._res_path;
			this->_headers = x._headers;
		}
		return *this;
	}

	std::string CGI::execCGI() {
		pid_t pid;
		int res;
		char **argv;
		int fd;
		int fds[2];

		argv = argsToArray();
		if (pipe(fds) == -1) {
			std::cout << "Pipe failed\n";
			throw ;
		}
		pid = fork();
		if (pid == 0) {
			close(fds[1]);
			dup2(fds[0], 0);
			fd = open("./www/cgi", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			if (fd < 0) {
				std::cout << "Failed to create file\n";
				throw ;
			}
			dup2(fd, 1);
			dup2(fd, 2);
			res = execve(_res_path.c_str(), argv, _envp);
			close(STDIN_FILENO);
			close(fd);
			close(fds[0]);
			exit(0);
		}
		else {
			close(fds[0]);
			write(fds[1], _req->getBody().c_str(), _req->getContentLength());
			close(fds[1]);
			waitpid(-1, NULL, 0);
			freeArray(argv);
			freeArray(envp);
		}
		return (readFile("./www/cgi"));
	}
}


