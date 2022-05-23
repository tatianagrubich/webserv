#ifndef INFOSERVER_HPP
# define INFOSERVER_HPP
# include <iostream>
# include <vector>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "Location.hpp"

#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define END "\033[0m"

typedef struct t_parametrs
{
	std::size_t listen;
	std::size_t methods;
	std::size_t root;
} t_parametrs;

class InfoServer
{
	std::string					str_from_config_file;
	t_parametrs					parametrs;
	std::string					ip;
	std::string					port;
	std::vector<std::string>	methods;
	std::string					root;
	struct sockaddr_in			addr;

	std::vector<Location>		locations;
	// static const int	bits = 8;
	void foundParametrsForServer(std::string source);
	void parsingListen(std::string source);
	void parsingMethods(std::string source);
	void parsingRoot(std::string source);
	bool isComment(std::string source);
	std::string deleteSpases(std::string source);

public:
	// InfoServer(void);
	// ~InfoServer(void);
	// InfoServer(const InfoServer &other);
	// InfoServer	&operator=(const InfoServer &other);
	void parsingStringForInfoServer(std::string source);
	void printInfoServer();
	void initSockAddrIn();
};

#endif
