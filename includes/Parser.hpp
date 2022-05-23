#ifndef PARSER_HPP
# define PARSER_HPP
# include <iostream>
# include <vector>
# include <fstream>
# include "InfoServer.hpp"

#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define END "\033[0m"

class Parser
{
	std::string config_file_name;
	std::vector<InfoServer> servers;
	std::ifstream fin;
	std::vector<std::string> file;
	int index;



	std::string string_from_config_file;
	// static const int	bits = 8;

	void errorConfigFile();
	// void analysisStringFromConfigFile();
	void createInfoServer();
	void readConfigFile();
	void foundInfoServers();

public:
	Parser(char *config_file_name);
	// ~InfoServer(void);
	// InfoServer(const InfoServer &other);
	// InfoServer	&operator=(const InfoServer &other);

	std::vector<InfoServer> parserConfigFile();
	void printServers();
};

#endif
