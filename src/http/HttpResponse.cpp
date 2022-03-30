#include "HTTPResponse.hpp"

ft::HTTPResponse::HTTPResponse(
	HTTPRequest* httpReuest,
	std::unordered_map<std::string,ft::VirtualHost>	&virtualHosts
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
	std::unordered_map<std::string,ft::VirtualHost>::const_iterator cit = _virtualHosts.cbegin();
	std::unordered_map<std::string,ft::VirtualHost>::const_iterator cend = _virtualHosts.cend();
	std::cout << "SERVER CONFIGURATIONS:\n";
	while(cit != cend) {
		std::cout << "\nhost_name: " << cit->first << ":\n";

		std::cout << "root: " << cit->second.getRoot() << std::endl;
		std::cout << "host: " << cit->second.getHost() << std::endl;
		std::cout << "port: " << cit->second.getPort() << std::endl;
		std::cout << "server_name: " << cit->second.getServerName() << std::endl;
		std::cout << "client_max_body_size: " << cit->second.getClientMaxBodySize() << std::endl;

		std::cout << "error pages: \n";
		std::unordered_map<short, std::string> errorPages = cit->second.getErrorPages();
		std::unordered_map<short, std::string>::const_iterator cit_er = errorPages.cbegin();
		std::unordered_map<short, std::string>::const_iterator cend_er = errorPages.cend();
		while (cit_er != cend_er) {
			std::cout << cit_er->first << "\t" << cit_er->second << std::endl;
			++cit_er;
		}

		std::cout << "\nlocations:\n";
		std::unordered_map<std::string, ft::Location> loc = cit->second.getLocations();
		std::unordered_map<std::string, ft::Location>::const_iterator cit_loc = loc.cbegin();
		std::unordered_map<std::string, ft::Location>::const_iterator cend_loc = loc.cend();
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
		++cit;
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
	if (!_httpReuest->getMethodName().compare("GET")) {
		handleGetResponse();
	} else if (!_httpReuest->getMethodName().compare("POST")) {

	} else if (!_httpReuest->getMethodName().compare("DELETE")) {

	} 

	// printConfigurations();			// this is for test. DELETE ME LATER!!!

}

void ft::HTTPResponse::setErrorResponse(int status, const std::string& description) {
	std::string	statusCode = std::to_string(status);

	_response =  _httpReuest->getHTTPVersion() + ' ' + statusCode + ' ' + description + "\r\n";
	_response += "Server: Tiny webserver\r\n\r\n";
	_response += "<html><head><title> " +  statusCode + ' ' + description + "</title></head>\
		<body><h1>ERROR " + description + "</h1></body></html>\r\n";
}

const std::string&	ft::HTTPResponse::getResponse() {
	return _response;
}


