#include "../../includes/utils.hpp"
#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

namespace ft {
	std::string readFile(std::string file) {
		char buffer[BUFFER_SIZE + 1] = {0};
		int fd;
		int i;
		int res;
		std::string result;

		fd = open(file.c_str(), O_RDONLY);
		if (fd < -1) {
			std::cout << "File does not exist" << std::endl;
			throw;
		}
		while ((res = read(fd, buffer, BUFFER_SIZE)) > 0) {
			result += buffer;
			i = 0;
			while (i < BUFFER_SIZE)
				buffer[i++] = 0;
		}
		if (res < 0) {
			std::cout << "Can not read file" << std::endl;
			throw;
		}
		close(fd);
		return (result);
	}

	std::string ITOS(size_t n) {
		std::ostringstream convert;

		convert << n;
		return (convert.str());
	}

	std::vector<unsigned char> readBinaryFile(std::string file) {
		char buffer[BUFFER_SIZE + 1] = {0};
		int fd;
		int i;
		int res;
		std::vector<unsigned char> result;

		fd = open(file.c_str(), O_RDONLY);
		if (fd < -1) {
			std::cout << "Error: file does not exist" << std::endl;
			throw;
		}
		while ((res = read(fd, buffer, BUFFER_SIZE)) > 0) {
			for (size_t j = 0; j < (size_t) res; ++j)
				result.push_back(buffer[j]);
			i = 0;
			while (i < BUFFER_SIZE)
				buffer[i++] = 0;
		}
		if (res < 0) {
			std::cout << "Error: can not read file" << std::endl;
			throw;
		}
		close(fd);
		return (result);
	}

	std::string replace(std::string source, std::string to_replace, std::string new_value) {
		size_t start_pos = 0;
		while ((start_pos = source.find(to_replace, start_pos)) != std::string::npos) {
			source.replace(start_pos, to_replace.length(), new_value);
			start_pos += new_value.length();
		}
		return (source);
	}

	int pathType(std::string path) {
		struct stat buffer;

		if (!stat(path.c_str(), &buffer)) {
			if (S_ISREG(buffer.st_mode))
				return (1);
			else
				return (2);
		} else
			return (0);
	}

	std::string getWithoutExtension(const std::string &str,
									const std::string &delim, size_t pos, short elem) {
		std::string::size_type found = 0;



		if (elem == 0) {
			found = str.find(delim, pos);
			return str.substr(pos, found - pos);
		}
		else if (elem == 1) {
			found = str.find_last_of(delim, str.size());
			std::cout << "FOUND: " << found << std::endl;
			std::cout << "POS: " << pos << std::endl;
			return  str.substr(found + 1, pos);
		}
		else {
			found = str.find(delim, pos);
			return str.substr(found + 1);
		}
	}
}