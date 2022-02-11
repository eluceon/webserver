#include <stdlib.h> // setenv
#include <iostream>
#include <unistd.h> // close function
#include <fcntl.h> // STDINOUT macros
#include <string>

extern char **environ;
#define ENV_CNT 19

static void	UnsetEnv(void) {
	unsetenv("AUTH_TYPE");
	unsetenv("CONTENT_LENGTH");
	unsetenv("CONTENT_TYPE");
	unsetenv("GATEWAY_INTERFACE");
	unsetenv("PATH_INFO");
	unsetenv("PATH_TRANSLATED");
	unsetenv("QUERY_STRING");
	unsetenv("REMOTE_ADDR");
	unsetenv("REMOTE_HOST");
	unsetenv("REMOTE_IDENT");
	unsetenv("REMOTE_USER");
	unsetenv("REQUEST_METHOD");
	unsetenv("SCRIPT_NAME");
	unsetenv("SERVER_NAME");
	unsetenv("SERVER_PORT");
	unsetenv("SERVER_PROTOCOL");
	unsetenv("SERVER_SOFTWARE");
	unsetenv("HTTP_ACCEPT");
	unsetenv("HTTP_USER_AGENT");
}

static void SetEnv(void) {
	setenv("AUTH_TYPE", "test", 1);
	setenv("CONTENT_LENGTH", "test", 1);
	setenv("CONTENT_TYPE", "test", 1);
	setenv("GATEWAY_INTERFACE", "test", 1);
	setenv("PATH_INFO", "test", 1);
	setenv("PATH_TRANSLATED", "test", 1);
	setenv("QUERY_STRING", "test", 1);
	setenv("REMOTE_ADDR", "test", 1);
	setenv("REMOTE_HOST", "test", 1);
	setenv("REMOTE_IDENT", "test", 1);
	setenv("REMOTE_USER", "test", 1);
	setenv("REQUEST_METHOD", "test", 1);
	setenv("SCRIPT_NAME", "test", 1);
	setenv("SERVER_NAME", "test", 1);
	setenv("SERVER_PORT", "test", 1);
	setenv("SERVER_PROTOCOL", "test", 1);
	setenv("SERVER_SOFTWARE", "test", 1);
	setenv("HTTP_ACCEPT", "test", 1);
	setenv("HTTP_USER_AGENT", "test", 1);
    while (*environ) {
        std::cout << *environ << std::endl;
        environ++;
    }
}

FILE*	CGI_caller() {
    FILE*       res;
    pid_t       pid;
    int			fildes[2];
    int			fd;
    char const*       argv[3];
    std::string		cgi_path;
    std::string		uri;

    SetEnv();
    cgi_path = "./cgi-bin/cgiscript.py";
    uri = "webpage";

    pipe(fildes);
    pid = fork();
    if (!pid) {
		dup2(fildes[0], STDIN_FILENO);
		close(fildes[0]);
		close(fildes[1]);
		fd = fileno(res);
		argv[0] = cgi_path.c_str();
		argv[1] = uri.c_str();
		argv[2] = NULL;
		dup2(fd, STDOUT_FILENO);
		if (execve(cgi_path.c_str(), (char *const *)argv, environ) == -1)
			exit(1);
    }
    else {
    	close(fildes[0]);
//    	write(fds[1], "c_style_str_body", "body_len"");
    	close(fildes[1]);
    	waitpid(pid, NULL, 0);
    }
    UnsetEnv();
    close(fd);
    return res;
}

int main() {
    CGI_caller();
    return 0;
}