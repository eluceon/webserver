#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <string>
# include <vector>
# include "HttpConstants.hpp"
# include "utils.hpp"

namespace ft {
	class Location {
		public:
			Location();
			Location(const Location & other);
			~Location();

			Location&	operator=(const Location & other);

			void	parseLocation(std::vector<std::string>::const_iterator &it,
						std::vector<std::string>::const_iterator &end, const char *curDir);

		private:
			std::string					_root;
			std::vector<bool>			_methods;
			bool						_autoindex;
			std::vector<std::string> 	_index;
			std::string					_fastcgiPass;
			unsigned long     			_maxBodySize;

	};
}


#endif