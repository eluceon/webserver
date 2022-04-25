#include "../../includes/HTTPResponse.hpp"

namespace ft {
	HTTPResponse::HTTPResponse(HTTPRequest* req, std::map<std::string,ft::VirtualHost> &vhost) : _req(req), _vhost(vhost) {
		init();
	}

	void HTTPResponse::init() {
		std::string server_name = getWithoutExtension(_req->getRelativePath(), "/", 1, 0);
		std::cout << "RELATIVE PATH: " << _req->getRelativePath() << std::endl;
		if (!_req->getRelativePath().find_last_of("/", 0) == _req->getRelativePath().size() - 1)
			_resource = getWithoutExtension(_req->getRelativePath(), "/", _req->getRelativePath().size(), 1);
		else
			_resource = "";
		if (server_name.size() == 0)
			server_name = "localhost";
		_headers = _req->getHeaders();
		getParams(server_name);
	}

	void HTTPResponse::getParams(const std::string &server_name) {
		std::map<std::string, ft::Location>	locations;
		size_t max_length;

		for (std::map<std::string, ft::VirtualHost>::iterator it = _vhost.begin(); it != _vhost.end(); ++it) {
			if (!it->first.compare(server_name)) {
				locations = it->second.getLocations();
			}
		}
		max_length = 0;

		for (std::map<std::string, ft::Location>::iterator it = locations.begin(); it != locations.end(); ++it) {
			if (_req->getRelativePath().find(it->first) != std::string::npos) {
				if (it->first.size() > max_length) {
					max_length = it->first.size();
					_res_path = it->second.getRoot();
					_index = it->second.getIndex();
					_autoindex = it->second.getAutoindex();
					_fastCGI = it->second.getFastcgiPass();
				}
			}
		}
	}

	HTTPResponse::~HTTPResponse(void) {}

	std::string HTTPResponse::getResponse(void) {
		std::string method = _req->getMethodName();
		_headers["Content-Type"] = getMIME(".html");

		if (!validMethod(method))
			return (getError(405));
		_res_path += _resource;
		if (pathType(_res_path) == 2) {
			if (_index.size() > 0) {
				for (std::vector<std::string>::iterator it = _index.begin(); it != _index.end(); ++it) {
					std::string path = _res_path + ((_res_path[_res_path.length() - 1] == '/') ? "" : "/") + *it;
					if (pathType(path) == 1) {
						_res_path = path;
						break ;
					}
				}
			}
			else {
				if (_autoindex) {
					return GetResponse(200, _headers, Autoindex(_res_path));
				}
				else {
					return getError(403);
				}
			}
		}
		if (pathType(_res_path) == 0)
			return getError(404);
		if (isCGIRequest()) {
			try {
				return CGIScript();
			}
			catch (const std::exception &e) {
				std::cerr << e.what() << std::endl;
				return getError(500);
			}
		}
		if (method == "GET")
			return sendGet(1);
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

		if (_fastCGI.size() == 0)
			return (false);
		i = _res_path.size() - 1;
		while (i > 0 && _res_path[i] != '.')
			--i;
		if (i >= _res_path.size())
			return (false);
		ext = std::string(_res_path, i + 1, _res_path.size() - i);
		for (size_t j = 0; j < _fastCGI.size(); ++j)
		{
			if (_fastCGI[j] == ext)
				return (true);
		}
		return (false);
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

	bool HTTPResponse::validMethod(std::string &method) {
		if (method == "GET" || method == "POST" || method == "DELETE") { return (true); }
		return (false);
	}

	std::string HTTPResponse::GetResponse() {
		return "";
	}

	std::string HTTPResponse::getError(size_t code) {
		std::string base;

		std::cout << "ERROR: " << code << std::endl;
		base = readFile("./www/error_pages/error.html");
		base = replace(base, "$1", ft::ITOS(code));
		base = replace(base, "$2", getStatus(code));
		std::cout << "BASE: " << base << std::endl;
		return (base);
	}

	std::string HTTPResponse::getStatus(size_t code) {
		std::map<std::size_t, std::string> rc;

		rc[100] = "Continue";
		rc[101] = "Switching Protocols";
		rc[200] = "OK";
		rc[201] = "Created";
		rc[202] = "Accepted";
		rc[203] = "Non-Authoritative Information";
		rc[204] = "No Content";
		rc[205] = "Reset Content";
		rc[206] = "Partial Content";
		rc[300] = "Multiple Choices";
		rc[301] = "Moved Permanently";
		rc[302] = "Found";
		rc[303] = "See Other";
		rc[304] = "Not Modified";
		rc[305] = "Use Proxy";
		rc[307] = "Temporary Redirect";
		rc[400] = "Bad Request";
		rc[401] = "Unauthorized";
		rc[402] = "Payment Required";
		rc[403] = "Forbidden";
		rc[404] = "Not Found";
		rc[405] = "Method Not Allowed";
		rc[406] = "Not Acceptable";
		rc[407] = "Proxy Authentication Required";
		rc[408] = "Request Timeout";
		rc[409] = "Conflict";
		rc[410] = "Gone";
		rc[411] = "Length Required";
		rc[412] = "Precondition Failed";
		rc[413] = "Payload Too Large";
		rc[414] = "URI Too Long";
		rc[415] = "Unsupported Media Type";
		rc[416] = "Range Not Satisfiable";
		rc[417] = "Expectation Failed";
		rc[426] = "Upgrade Required";
		rc[500] = "Internal Server Error";
		rc[501] = "Not Implemented";
		rc[502] = "Bad Gateway";
		rc[503] = "Service Unavailable";
		rc[504] = "Gateway Timeout";
		rc[505] = "HTTP Version Not Supported";
		return rc[code];
	}

	std::string HTTPResponse::sendGet(void) {
		return "";
	}

	std::string HTTPResponse::sendPost(void) {
		return "";
	}
	std::string HTTPResponse::sendDelete() {
		return "";
	}
}