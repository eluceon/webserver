#include "../../includes/HTTPResponse.hpp"
#include <dirent.h>

namespace ft {
	HTTPResponse::HTTPResponse(HTTPRequest* req, std::map<std::string, ft::VirtualHost> &vhost) : _req(req), _vhost(vhost) {
		init();
	}

//	HTTPResponse::HTTPResponse(const HTTPResponse &x) {
//		*this = x;
//	}

	HTTPResponse &HTTPResponse::operator=(const HTTPResponse &x) {
		if (this != &x) {
			this->_headers = x._headers;
			this->_req = x._req;
			this->_res = x._res;
			this->_res_path = x._res_path;
			this->_location = x._location;
			this->_vhost = x._vhost;
			this->_index = x._index;
			this->_autoindex = x._autoindex;
			this->_fastCGI = x._fastCGI;
		}
		return *this;
	}

	HTTPResponse::~HTTPResponse() {}

	void HTTPResponse::init() {
		_headers = _req->getHeaders();
		getParams();
		_res = cleanURI(_req->getRelativePath());
	}

	std::string HTTPResponse::cleanURI(std::string rel_path)
	{
		std::string res;
		size_t i;

		i = 0;
		res = rel_path;
		res.replace(0, _location.size(), "/");
		res = replace(res, "//", "/");
		while (res[i] && res[i] != '?')
			++i;
		res = std::string(res, 0, i);
		return (res);
	}

	void HTTPResponse::getParams(void) {
		std::map<std::string, ft::Location>	locations;
		size_t max_length;
		std::string server_name = _req->getServerName();

		for (std::map<std::string, ft::VirtualHost>::iterator it = _vhost.begin(); it != _vhost.end(); ++it) {
//			if (!it->first.compare(server_name)) {
			if (it->second.getPort() == _req->getPort()) {
				locations = it->second.getLocations();
			}
		}
		max_length = 0;

		for (std::map<std::string, ft::Location>::iterator it = locations.begin(); it != locations.end(); ++it) {
			if (_req->getRelativePath().find(it->first) != std::string::npos) {
				if (it->first.size() > max_length) {
					max_length = it->first.size();
					_location = it->first;
					if (it->second.getReturn().size() > 0) { _res_path = it->second.getReturn(); }
					else { _res_path = it->second.getRoot(); }
					_index = it->second.getIndex();
					_autoindex = it->second.getAutoindex();
					_fastCGI = it->second.getFastcgiPass();
				}
			}
		}
	}

	std::string HTTPResponse::getResponse(void) {
		std::string method = _req->getMethodName();
		_headers["Content-Type"] = getMIME("dummy.html");

		if (!validMethod(method))
			return (GetResponse(405, getError(405)));
		if (_res_path[_res_path.size() - 1] == '/') {
			_res_path = std::string(_res_path, 0, _res_path.size() - 1);
		}
		_res_path += _res;
		if (pathType(_res_path) == 2) {
			if (!_index.empty()) {
				_res_path += ((_res_path[_res_path.length() - 1] == '/') ? "" : "/");
				for (std::vector<std::string>::iterator it = _index.begin(); it != _index.end(); ++it) {
					std::string path = _res_path + *it;
					if (pathType(path) == 1) {
						_res_path = path;
						break ;
					}
				}
			}
			else {
				if (_autoindex) {
					return GetResponse(200, Autoindex());
				}
				else {
					return GetResponse(403, getError(403));
				}
			}
		}
		if (pathType(_res_path) == 0)
			return GetResponse(404, getError(404));
		if (isCGIRequest()) {
			try {
				return GetResponse(200, CGI(_res, _res_path, _req).execCGI());
			}
			catch (...) {
				return GetResponse(500, getError(500));
			}
		}
		if (method == "GET")
			return sendGet();
		else if (method == "POST")
			return sendPost();
		else if (method == "DELETE")
			return sendDelete();
		return ("");
	}

	bool HTTPResponse::isCGIRequest(void)
	{
		size_t i;
		std::string ext;
		std::string cgi_ext;

		if (_fastCGI.empty())
			return (false);
		i = _res_path.size() - 1;
		while (i > 0 && _res_path[i] != '.')
			--i;
		if (i >= _res_path.size())
			return (false);
		ext = std::string(_res_path, i + 1, _res_path.size() - i);
		cgi_ext = _location.substr(_location.find(".") + 1, _location.size() - _location.find("."));
		if (ext == cgi_ext) {
			return (true);
		}
		return (false);
	}

	bool HTTPResponse::validMethod(std::string &method) {
		if (method == "GET" || method == "POST" || method == "DELETE") { return (true); }
		return (false);
	}

	std::string HTTPResponse::getError(size_t code) {
		std::string error;

		error = readFile("./www/error_pages/error.html");
		error = replace(error, "$1", ft::ITOS(code));
		error = replace(error, "$2", getStatus(code));
		return (error);
	}

	std::string HTTPResponse::sendGet(void) {
		std::string content;

		try {
			content = readFile(_res_path);
			_headers["Content-Type"] = getMIME(_res_path);
			return (GetResponse(200, content));
		}
		catch (const std::exception &e) {
			return (GetResponse(403, ""));
		}
	}

	std::string HTTPResponse::sendPost() {
		int fd;
		int rtn;
		int type;
		std::string path;
		std::string content;
		std::map<std::string, std::string>::iterator it;

		if (_req->getQueryString().size() > _location.size())
		{
			std::string file = std::string(_req->getQueryString(), _location.size());
			path = _res_path + "/" + file;
		}
		else
			path = _res_path;
		type = pathType(path);
		it = _headers.begin();
		while (it != _headers.end()) {
			content += it->first + ": " + it->second + "\r\n";
			++it;
		}
		try
		{
			if (type == 1)
			{
				if ((fd = open(path.c_str(), O_WRONLY | O_TRUNC, 0644)) == -1)
					return "Unable to open file";
				write(fd, content.c_str(), content.length());
				close(fd);
				rtn = 200;
				_headers["Content-Location"] = _res_path;
			}
			else if (type == 0)
			{
				if ((fd = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0644)) == -1)
					return GetResponse(500, getError(500));
				write(fd, content.c_str(), content.length());
				close(fd);
				rtn = 201;
				_headers["Location"] = _res_path;
			}
			else
				return GetResponse(500, getError(500));
		}
		catch (std::exception & ex)
		{
			throw ;
		}
		return GetResponse(rtn, "");
	}

	std::string HTTPResponse::sendDelete() {
		if (pathType(_res_path) == 1)
		{
			unlink(_res_path.c_str());
			return (GetResponse(200, ""));
		}
		return GetResponse(404, getError(404));
	}

	std::string HTTPResponse::GetResponse(size_t code, std::string content)
	{
		char *temp;
		std::string response;
		std::map<std::string, std::string>::iterator it;

		temp = (char *)malloc(sizeof(char) * content.size() + 1);
		unsigned long i = 0;
		while (i < content.size()) {
			temp[i] = content[i];
			i++;
		}
		temp[i] = 0;
		_headers["Content-Length"] = ft::ITOS(content.size());
		_headers["Server"] = "WebServer 21";
		_headers["Date"] = ft::getDate();
		response += "HTTP/1.1 ";
		response += ft::ITOS(code) + " ";
		response += getStatus(code) + "\r\n";
		it = _headers.begin();
		while (it != _headers.end()) {
			response += it->first + ": " + it->second + "\r\n";
			++it;
		}
		response += "\r\n";
		for (size_t i = 0; i < content.size(); ++i)
			response += temp[i];
		free(temp);
		std::cout << "RES: " << _res << std::endl;
		std::cout << "RES PATH: " << _res_path << std::endl;
		return (response);
	}

	std::string HTTPResponse::getMIME(std::string file) {
		std::map<std::string, std::string> MIME;
		std::string ext;
		size_t i;

		i = file.size() - 1;
		while (i > 0 && file[i] != '.')
			--i;
		if (i == 0)
			return ("text/plain");
		ext = std::string(file, i + 1, file.size() - i);
		MIME["aac"] = "audio/aac";
		MIME["abw"] = "application/x-abiword";
		MIME["arc"] = "application/octet-stream";
		MIME["avi"] = "video/x-msvideo";
		MIME["azw"] = "application/vnd.amazon.ebook";
		MIME["bin"] = "application/octet-stream";
		MIME["bmp"] = "image/bmp";
		MIME["bz"] = "application/x-bzip";
		MIME["bz2"] = "application/x-bzip2";
		MIME["csh"] = "application/x-csh";
		MIME["css"] = "text/css";
		MIME["csv"] = "text/csv";
		MIME["doc"] = "application/msword";
		MIME["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
		MIME["eot"] = "application/vnd.ms-fontobject";
		MIME["epub"] = "application/epub+zip";
		MIME["gif"] = "image/gif";
		MIME["htm"] = "text/html";
		MIME["html"] = "text/html";
		MIME["ico"] = "image/x-icon";
		MIME["ics"] = "text/calendar";
		MIME["jar"] = "application/java-archive";
		MIME["jpeg"] = "image/jpeg";
		MIME["jpg"] = "image/jpeg";
		MIME["js"] = "application/javascript";
		MIME["json"] = "application/json";
		MIME["mid"] = "audio/midi";
		MIME["midi"] = "audio/midi";
		MIME["mpeg"] = "video/mpeg";
		MIME["mpkg"] = "application/vnd.apple.installer+xml";
		MIME["odp"] = "application/vnd.oasis.opendocument.presentation";
		MIME["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
		MIME["odt"] = "application/vnd.oasis.opendocument.text";
		MIME["oga"] = "audio/ogg";
		MIME["ogv"] = "video/ogg";
		MIME["ogx"] = "application/ogg";
		MIME["otf"] = "font/otf";
		MIME["png"] = "image/png";
		MIME["pdf"] = "application/pdf";
		MIME["ppt"] = "application/vnd.ms-powerpoint";
		MIME["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
		MIME["rar"] = "application/x-rar-compressed";
		MIME["rtf"] = "application/rtf";
		MIME["sh"] = "application/x-sh";
		MIME["svg"] = "image/svg+xml";
		MIME["swf"] = "application/x-shockwave-flash";
		MIME["tar"] = "application/x-tar";
		MIME["tif"] = "image/tiff";
		MIME["tiff"] = "image/tiff";
		MIME["ts"] = "application/typescript";
		MIME["ttf"] = "font/ttf";
		MIME["vsd"] = "application/vnd.visio";
		MIME["wav"] = "audio/x-wav";
		MIME["weba"] = "audio/webm";
		MIME["webm"] = "video/webm";
		MIME["webp"] = "image/webp";
		MIME["woff"] = "font/woff";
		MIME["woff2"] = "font/woff2";
		MIME["xhtml"] = "application/xhtml+xml";
		MIME["xls"] = "application/vnd.ms-excel";
		MIME["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
		MIME["xml"] = "application/xml";
		MIME["xul"] = "application/vnd.mozilla.xul+xml";
		MIME["zip"] = "application/zip";
		MIME["3gp"] = "audio/3gpp";
		MIME["3g2"] = "audio/3gpp2";
		MIME["7z"] = "application/x-7z-compressed";
		if (MIME.count(ext))
			return (MIME[ext]);
		return ("application/octet-stream");
	}

	std::string HTTPResponse::getStatus(size_t code) {
		std::map<std::size_t, std::string> s;

		s[100] = "Continue";
		s[101] = "Switching Protocols";
		s[200] = "OK";
		s[201] = "Created";
		s[202] = "Accepted";
		s[203] = "Non-Authoritative Information";
		s[204] = "No Content";
		s[205] = "Reset Content";
		s[206] = "Partial Content";
		s[300] = "Multiple Choices";
		s[301] = "Moved Permanently";
		s[302] = "Found";
		s[303] = "See Other";
		s[304] = "Not Modified";
		s[305] = "Use Proxy";
		s[307] = "Temporary Redirect";
		s[400] = "Bad Request";
		s[401] = "Unauthorized";
		s[402] = "Payment Required";
		s[403] = "Forbidden";
		s[404] = "Not Found";
		s[405] = "Method Not Allowed";
		s[406] = "Not Acceptable";
		s[407] = "Proxy Authentication Required";
		s[408] = "Request Timeout";
		s[409] = "Conflict";
		s[410] = "Gone";
		s[411] = "Length Required";
		s[412] = "Precondition Failed";
		s[413] = "Payload Too Large";
		s[414] = "URI Too Long";
		s[415] = "Unsupported Media Type";
		s[416] = "Range Not Satisfiable";
		s[417] = "Expectation Failed";
		s[426] = "Upgrade Required";
		s[500] = "Internal Server Error";
		s[501] = "Not Implemented";
		s[502] = "Bad Gateway";
		s[503] = "Service Unavailable";
		s[504] = "Gateway Timeout";
		s[505] = "HTTP Version Not Supported";
		return s[code];
	}

	std::string HTTPResponse::Autoindex() {
		std::string res;
		std::string content;
		struct dirent *entry;
		DIR *dir;

		res = readFile("./www/autoindex.html");
		res = replace(res, "$1", _res);
		dir = opendir(_res_path.c_str());
		while ((entry = readdir(dir)) != 0)
			content += "<li><a href=\"localhost:8080" + _location + "/" + std::string(entry->d_name) +  "\">" + std::string(entry->d_name) + "</a></li>";
		closedir(dir);
		res = replace(res, "$2", content);
		return (res);
	}
}