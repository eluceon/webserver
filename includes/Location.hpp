#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <string>
# include <vector>
# include "HttpConstants.hpp"

namespace ft {
	class Location {
		public:
			Location();
			Location(const Location & other);
			~Location();

			Location&	operator=(const Location & other);

		private:
			std::string					_root;
			bool						_methods[NUMBER_OF_METHODS];
			bool						_autoindex;
			std::vector<std::string> 	_index;
			std::string					_fastcgiPass;

	};
}


#endif