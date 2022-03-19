#include <cstdlib> //env
#include <stdlib.h> //env
#include <iostream>
#include <unistd.h> // close function
#include <fcntl.h> // STDINOUT macros
#include <string>
#include "./includes/HttpRequest.hpp"

namespace ft {
    class CGI {
        public:
            CGI(HttpRequest &rec) {};
            ~CGI() {};
        private:
            CGI(void);
            CGI(const CGI &x);
            CGI &operator=(const CGI &x);

            void    SetEnv(HttpRequest &rec);
            std::string CGIscript(std::string& script);
            char    **ArrayToStr(void);

            class AllocException : public std::exception	{
            public:
                const char* what() const throw(); };

			std::string							_body;
            std::map<std::string, std::string>	_env;
    };
}
