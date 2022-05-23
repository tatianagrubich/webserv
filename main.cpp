#include "includes/Webserv.hpp"

int main(int argc, char **argv)
{
	if (argc != 2 || !errorProgramName(argv[0]))
	{
		std::cerr << "Error argument" << std::endl;
		return (-1);
	}
	Parser parser(argv[1]);
	std::vector<InfoServer> servers = parser.parserConfigFile();
	parser.printServers();



	return (0);
}


