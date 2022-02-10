#include <string>
#include <iostream>

#define ENV_CNT 19


FILE*	CGI_caller(request &req, std::string const &cgi_path) {
    std::FILE   res;
    pid_t       pid;
    char*       argv[3];
    char*       envp[ENV_CNT];

    const std::string env[ENV_CNT] = {
    "AUTH_TYPE", "CONTENT_LENGTH", "CONTENT_TYPE", "GATEWAY_INTERFACE", "PATH_INFO", "PATH_TRANSLATED",
    "QUERY_STRING", "REMOTE_ADDR", "REMOTE_HOST", "REMOTE_IDENT", "REMOTE_USER", "REQUEST_METHOD",
    "SCRIPT_NAME", "SERVER_NAME", "SERVER_PORT", "SERVER_PROTOCOL", "SERVER_SOFTWARE",
    "HTTP_ACCEPT", "HTTP_USER_AGENT"
    };

    for (int i = 0; i < ENV_CNT; ++i) {
        std::cout << env[i] << std::endl;
    }
}

int main() {
    CGI_caller(NULL, ".");
    return 0;
}