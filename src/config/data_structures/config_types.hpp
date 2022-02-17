#pragma once

#include <string>
#include <map>
#include <list>

/*
    STRL: List of strings
    - server_name
    - index
    - methods
*/

typedef std::list<std::string> t_strl;


/*
    IPP: Struct ip:port
    - listen

    NB: will require operators, see below
*/

typedef struct s_ipp{
    int ip;
    std::string port;
};

bool    operator==(s_ipp const &left, s_ipp const &right) {
    return (left.ip == right.ip && left.port == right.port);
}

bool    operator!=(s_ipp const &left, s_ipp const &right) {
    return (!(left == right));
}

/*
    FASTCGI: Map string:string
    - fastcgi_pass __PWD__/__PHP__ (PWD:PHP)
*/
typedef std::map<std::string, std::string> t_fastcgi;

/*
    ERROR: Map int:string
*/

typedef std::map<int, std::string> t_error;

/*
    LOCATION: Class containing location parameters.
    It's class, because it should be operable with internal and non-member overloads.
*/

class c_location{
    public:
        c_location() : max_body_size(-1) {return ;}
        c_location(c_location const &from) {*this = from;}
        virtual ~c_location() {return ;};

        c_location &operator=(c_location const &from)
        {
            this->root = from.root;
            this->index = from.index;
            this->route = from.route;
            this->methods = from.methods;
            this->autoindex = from.autoindex;
            this->error_page = from.error_page;
            this->fastcgi_pass = from.fastcgi_pass;
            this->fastcgi_param = from.fastcgi_param;
            this->max_body_size = from.max_body_size;
            return (*this);
        }

        std::string root;
        t_strl index;
        t_strl methods;
        std::string route;
        bool autoindex;
        t_error error_page;
        std::string fastcgi_pass;
        t_fastcgi fastcgi_param;
        int max_body_size;
};