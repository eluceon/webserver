#include "utils.hpp"

namespace ft {
	void	skipTokens(std::vector<std::string>::const_iterator &it,
					std::vector<std::string>::const_iterator &end,
					size_t n, const char *neededToken) {
	while (it != end && n-- > 0)
		++it;
	if (it == end || (neededToken && it->compare(neededToken)))
		ft::errorExit("Invalid config file");
}
}