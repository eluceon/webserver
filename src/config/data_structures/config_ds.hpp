#pragma once

#include <iostream>
#include "./config_types.hpp"

/*
    CONFIG_DS:
    Main config data structure, includes config_types.
*/

class config_ds
{
    public:
        config_ds(void);
        config_ds(config_ds const &from);
        virtual ~config_ds();

        config_ds &operator=(config_ds const &from);

        // Server parameters:
        int server_id;
        int max_body_size;
        s_ipp listen;
        t_strl index;
        t_strl server_name;
        std::string root;
        bool autoindex;
        t_fastcgi fastcgi_param;
        t_error error_page;

        // Location parameters:
        std::list<c_location> location;
};