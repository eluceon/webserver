#include "./config_ds.hpp"

config_ds::config_ds() : max_body_size(0), server_id(0)
{

}

config_ds::config_ds(config_ds const &from)
{
    *this = from;
}

config_ds::~config_ds()
{

}

config_ds &config_ds::operator=(config_ds const &from)
{
    this->server_id = from.server_id;
    this->max_body_size = from.max_body_size;
    this->listen = from.listen;
    this->index = from.index;
    this->server_name = from.server_name;
    this->root = from.root;
    this->autoindex = from.autoindex;
    this->fastcgi_param = from.fastcgi_param;
    this->error_page = from.error_page;
    this->location = from.location;
    
    return (*this);
}