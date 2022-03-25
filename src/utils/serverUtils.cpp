#include <fstream>
#include <iomanip>
#include "utils.hpp"

namespace ft
{	
	/*
	* This function writes a timestamp string to the open fileLog 
	*/ 
	void timestamp(const std::string& msg) {
		std::fstream	fout("./logs/webserver.log", std::ios_base::out | std::ios_base::app);

		if ((fout.rdstate() & std::ifstream::failbit) != 0 )
			std::cerr << "Error opening 'webserver.log'" << std::endl;
		else {
			std::time_t timer = time(&timer);
			fout << std::put_time(std::localtime(&timer), "%d/%m/%Y %H:%M:%S> ")
					<< msg << '\n';
		}
		if ((fout.rdstate() & std::ifstream::badbit) != 0 ) {
			std::cerr << "Writing 'webserver.log' error" << std::endl;
		}
	}

	std::string	Getcwd() {
		char		*cwd;
		std::string	currentDir;

		cwd = getcwd(NULL, 0);
		if (!cwd)
			ft::systemErrorExit("getcwd");
		currentDir = cwd;
		free(cwd);
		return currentDir;
	}
}
