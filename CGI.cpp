#include "CGI.hpp"

ft::CGI::CGI(void) : _body("") {}

ft::CGI::CGI(HttpRequest &rec) : _body("") { SetEnv(rec); }

ft::CGI::CGI(const CGI &x) {
	if (this != &x) {
		*this = x;
	}
}

ft::CGI	&ft::CGI::operator=(const CGI &x) {
	if (this != &x) {
		_body = x._body;
		_env = x._env;
	}
	return *this;
}

ft::CGI::~CGI(void) {}

void	ft::CGI::SetEnv(HttpRequest &rec) {

    // == SERVER VARIABLES == //

    _env["GATEWAY_INTERFACE"] = "CGI/1.1"; // CGI Interface version
    _env["SERVER_NAME"] = rec.getServerName(); // Server IP or domain name
    _env["SERVER_PORT"] = rec.getPort(); // Http request port
    _env["SERVER_PROTOCOL"] = rec.getProtocol(); // Http protocol version
    _env["SERVER_SOFTWARE"] = "Red Hat/Linux"; // Server OS name

    // == REQUEST VARIABLES == //

    _env["AUTH_TYPE"] = "Basic"; // Server authorization type
    // _env["CONTENT_FILE"] = ""; Windows servers only
    _env["CONTENT_LENGTH"] = rec.getContentLength(); // Bytes to read from stdin
    _env["CONTENT_TYPE"] = "text/html"; // Content type sent from client to server
    // _env["OUTPUT_FILE"] = ""; // Windows servers only
    _env["PATH_INFO"] = ""; // Additional path eg: http://.../cgi-bin/1.cgi/dir1/dir2   Here the dir1/dir2 segment
    _env["PATH_TRANSLATED"] = ""; // as above: /home/httpd/html/dir1/dir2
    _env["QUERY_STRING"] = rec.getQueryString().c_str; // URL data. In htttp://.../cgi-bin/1.cgi?d=123&name=kirill Q_S will be d=123&name=kirill
    _env["REMOTE_ADDR"] = ""; // IP address of user requesting the interface
    _env["REMOTE_HOST"] = ""; // User DNS?
    _env["REQUEST_METHOD"] = rec.getMethodName().c_str(); // GET POST or DELETE
    _env["REQUEST_LINE"] = ""; // HTTP query string eg: GET /cgi-bin/1.cgi HTTP/1.0
    _env["SCRIPT_NAME"] = ""; // Script name eg: 1.cgi

    // == CLIENT VARIABLES == /

    std::map<std::string, std::string> headers = rec.getHeaders(); // HTTP_ACCEPT, HTTP_USER_AGENT, HTTP_ACCEPT_ENCODING, HTTP_ACCEPT_LANGUAGE, HTTP_IF_MODIFIED_SINCE, HTTP_FROM
}

char    **ArrayToStr(void) {
    char **env = new char[][_env.size() + 1];
    int i = 0;

    for (std::map<std::string, std::string>::iterator it = _env.begin(); it != _env.end(); ++it, i++) {
        std::string tmp = it->first.append('=', it->second);
        env[i] = new char[tmp.size() + 1];
        env[i] = tmp.c_str();
    }
    env[i] = NULL;
    return env;
}

FILE *ft::CGI::CGIscript(std::string& script) {
    char **env;

    try {
        env = ArrayToStr();
    }
    catch (ft::CGI::AllocException &e) {
        std::cout << e.what();
    }
}

const char *ft::CGI::AllocException::what() const throw() {
	return "Allocation failed";
}

int main() {
    ft::CGI cgiscript = new ft::CGI();
    cgiscript.CGIscript("path");
    return 0;
}
