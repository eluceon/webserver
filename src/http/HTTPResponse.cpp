#include "HTTPResponse.hpp"

ft::HTTPResponse::HTTPResponse(
	HTTPRequest* httpReuest,
	std::map<std::string,ft::VirtualHost>	&virtualHosts
)
	: _httpReuest(httpReuest),
	_virtualHosts(virtualHosts),
	_response("")
{
	run();
}
ft::HTTPResponse::HTTPResponse(const HTTPResponse& other)
	: _httpReuest(other._httpReuest),
	_virtualHosts(other._virtualHosts),
	_response(other._response)
{}

ft::HTTPResponse::~HTTPResponse() {}

ft::HTTPResponse &ft::HTTPResponse::operator=(const HTTPResponse &other) {
	if (this != &other) {
		_httpReuest = other._httpReuest;
		_virtualHosts = other._virtualHosts;	
		_response = other._response;
	}
	return *this;
}

/*
* this method for testing configurations. DELETE IT LATER!!!
*/
void ft::HTTPResponse::printConfigurations() {
	std::map<std::string,ft::VirtualHost>::iterator it = _virtualHosts.begin();
	std::map<std::string,ft::VirtualHost>::iterator end = _virtualHosts.end();
	std::cout << "SERVER CONFIGURATIONS:\n";
	while(it != end) {
		std::cout << "\nhost_name: " << it->first << ":\n";

		std::cout << "root: " << it->second.getRoot() << std::endl;
		std::cout << "host: " << it->second.getHost() << std::endl;
		std::cout << "port: " << it->second.getPort() << std::endl;
		std::cout << "server_name: " << it->second.getServerName() << std::endl;
		std::cout << "client_max_body_size: " << it->second.getClientMaxBodySize() << std::endl;

		std::cout << "error pages: \n";
		std::map<short, std::string> errorPages = it->second.getErrorPages();
		std::map<short, std::string>::iterator cit_er = errorPages.begin();
		std::map<short, std::string>::iterator cend_er = errorPages.end();
		while (cit_er != cend_er) {
			std::cout << cit_er->first << "\t" << cit_er->second << std::endl;
			++cit_er;
		}

		std::cout << "\nlocations:\n";
		std::map<std::string, ft::Location> loc = it->second.getLocations();
		std::map<std::string, ft::Location>::iterator cit_loc = loc.begin();
		std::map<std::string, ft::Location>::iterator cend_loc = loc.end();
		while (cit_loc != cend_loc) {
			std::cout << cit_loc->first << "\n";
			std::cout << " - root: " << cit_loc->second.getRoot() << std::endl;
			std::cout << " - return : " << cit_loc->second.getReturn() << std::endl;
			std::cout << " - methods : ";
			for (size_t i = 0; i < cit_loc->second.getMethods().size(); ++i) {
				if (i == GET && cit_loc->second.getMethods()[GET])
					std::cout << "GET ";
				else if (i == POST && cit_loc->second.getMethods()[POST])
					std::cout << "POST ";
				else if (i == DELETE && cit_loc->second.getMethods()[DELETE])
					std::cout << "DELETE ";
				else if (i == PUT && cit_loc->second.getMethods()[PUT])
					std::cout << "PUT ";
			}
			std::cout << "\n - autoindex: " << (cit_loc->second.getAutoindex() ? "on\n" : "off\n");
			std::cout << " - index: " << std::endl;
			std::vector<std::string> idx = cit_loc->second.getIndex();
			for (size_t i = 0; i < idx.size(); ++i) {
				std::cout << idx[i] << ' ';
			}
			std::cout << "\n - fastcgi_pass : " << cit_loc->second.getFastcgiPass() << std::endl;
			std::cout << " - client_max_body_size : " << cit_loc->second.getClientMaxBodySize() << std::endl;
			++cit_loc;
		}
		++it;
	}
}

void ft::HTTPResponse::handleGetResponse() {
	if (_httpReuest->getStatus() == HTTP_OK ) {
		// _httpReuest->getRelativePath();
		std::ifstream	siteFile("./www/site1/index.html");
		if ((siteFile.rdstate() & std::ifstream::failbit) != 0 ) {
			setErrorResponse(HTTP_NOT_FOUND, "NOT FOUND");
		} else {
			_response = _httpReuest->getHTTPVersion() + " 200 OK\r\n";
			_response += "Server: ft_server\r\n\r\n";
			std::string line;
			while (getline (siteFile, line))
				_response.append(line);
			siteFile.close();
		}
	} else {

	}
}


void ft::HTTPResponse::handlePostResponse() {
	std::cout << "TEST POST...\n"; 			//  DELETE ME!!!
}

void ft::HTTPResponse::handleDeleteResponse() {
	std::cout << "TEST DELETE...\n"; 		//  DELETE ME!!!
}

void ft::HTTPResponse::run() {
	if (_httpReuest->getStatus() != HTTP_OK) {
		setErrorResponse(_httpReuest->getStatus(), "");
	} else if (!_httpReuest->getMethodName().compare("GET")) {
		handleGetResponse();
	} else if (!_httpReuest->getMethodName().compare("POST")) {

	} else if (!_httpReuest->getMethodName().compare("DELETE")) {

	} 

	// printConfigurations();			// this is for test. DELETE ME LATER!!!

}

void ft::HTTPResponse::setErrorResponse(int status, const std::string& description) {
	std::string	statusCode = ft::to_string(status);

	_response =  _httpReuest->getHTTPVersion() + ' ' + statusCode + ' ' + description + "\r\n";
	_response += "Server: Ft webserver\r\n\r\n";
	_response += "<html><head><title> " +  statusCode + ' ' + description + "</title></head>\
		<body><h1>ERROR " + description + "</h1></body></html>\r\n";
}

const std::string&	ft::HTTPResponse::getResponse() {
	return _response;
}


