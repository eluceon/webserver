#include <cstdlib> //env
#include <stdlib.h> //env
#include <iostream>
#include <unistd.h> // close function
#include <fcntl.h> // STDINOUT macros
#include <string>
#include "./includes/HttpRequest.hpp"

#define ENV_CNT 19
extern char **environ;

namespace ft {
    class CGI {
        public:
            CGI(HttpRequest &rec) {};
        private:
            CGI(void) {}; 
            CGI(const CGI &x);
            ~CGI() {};

            CGI& operator=(const CGI &x);

            void    SetEnv(HttpRequest &rec);
            void    UnsetEnv(void);
            std::string getContent(void);
            char toUpper(char c);
            char toDec(char c);
            char *getParameter(char *buffer, char *name);
            void    parseStrGet(void);
            void    parseStrPost(void);
            void    setLen(void);
            std::string    readLenBytes(void);

            class LengthException : public std::exception	{ const char* what() const throw(); };
            class AllocException : public std::exception	{ const char* what() const throw(); };

            std::string     _method;
            std::string     _query_string;
            u_long          _content_length;
    };
}
