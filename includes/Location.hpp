#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <string>
# include <vector>
# include "HttpConstants.hpp"
# include "utils.hpp"

namespace ft {
	class Location {
		public:
			Location(const std::string& currentDir = "");
			Location(const Location &other);
			~Location();

			Location&	operator=(const Location & other);

			void	parseLocation(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end,
						const std::string &curDir);
			void	setRoot(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end);
			void	setMethods(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end);
			void	setAutoindex(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end);
			void	setIndex(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end);
			void	setClientMaxBodySize(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end);
			void	setFastcgiPass(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end);
			void	setReturn(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end);

		private:
			std::string					_root;
			std::string					_return;
			std::vector<bool>			_methods;
			bool						_autoindex;
			std::vector<std::string> 	_index;
			std::string					_fastcgiPass;
			unsigned long     			_clientMaxBodySize;

	};
}


#endif