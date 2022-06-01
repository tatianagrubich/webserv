#ifndef INFOSERVER_HPP
#define INFOSERVER_HPP
#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Location.hpp"

#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define END "\033[0m"

typedef struct s_parametrs
{
	std::size_t listen;
	std::size_t methods;
	std::size_t root;
	std::size_t autoindex;
} t_parameters;

class InfoServer
{
	std::string str_from_config_file;
	t_parameters parameters;
	std::string ip;
	std::string port;
	std::string root;
	std::vector<std::string> methods;
	struct sockaddr_in addr;
	bool autoindexFlag;
	std::vector<Location> locations;

	void foundParametrsForServer(std::string source);
	void parsingListen(std::string source);
	void parsingMethods(std::string source);
	void parsingRoot(std::string source);
	void parsingAutoindex(std::string source);
	bool isComment(std::string source);
	std::string deleteSpases(std::string source);

public:
	void parsingStringForInfoServer(std::string source);
	void printInfoServer();
	void initSockAddrIn();
	void addLocation(Location location);
	bool getAutoindexFlag();
	std::string getPort();
	std::string getRoot();
	std::vector<std::string> getMethods();
};

#endif
