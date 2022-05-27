#include "../includes/InfoServer.hpp"

// InfoServer::InfoServer()
// {
// }
// 	InfoServer::~InfoServer(void)
// 	{

// 	}
// 	InfoServer::InfoServer(const InfoServer &other)
// 	{

// 	}
// 	InfoServer	&InfoServer::operator=(const InfoServer &other)
// 	{

// 	}
void InfoServer::parsingStringForInfoServer(std::string source)
{
	foundParametrsForServer(source);
	if(parameters.listen != std::string::npos)
	{
		parsingListen(source);
	}
	else if (parameters.methods != std::string::npos)
	{
		parsingMethods(source);
	}
	else if (parameters.root != std::string::npos)
	{
		parsingRoot(source);
	}
}

void InfoServer::foundParametrsForServer(std::string source)
{
	parameters.listen = source.find("listen");
	parameters.methods = source.find("methods");
	parameters.root = source.find("root");
}

void InfoServer::parsingListen(std::string source)
{
	std::size_t pos = 0;

	if(!isComment(source))
	{
		return ;
	}
	source.erase(parameters.listen, strlen("listen"));
	source = deleteSpases(source);
	pos = source.find(":", pos);
	ip = source.substr(0, pos);
	port = source.substr(pos + 1, source.length());
}

void InfoServer::parsingMethods(std::string source)
{
	if(!isComment(source))
	{
		return ;
	}
	source.erase(parameters.methods, strlen("methods"));
	source = deleteSpases(source);

	std::size_t pos = 0;
	std::size_t next = 0;


	while((next = source.find(" ", pos)) != std::string::npos)
	{
		methods.push_back(source.substr(pos, next - pos));
		pos = next + 1;
	}
	methods.push_back(source.substr(pos, next - pos));
}

void InfoServer::parsingRoot(std::string source)
{
	if(!isComment(source))
	{
		return ;
	}
	source.erase(parameters.root, strlen("root"));
	source = deleteSpases(source);
	root = source;
}

bool InfoServer::isComment(std::string source)
{
	std::size_t pos = 0;

	pos = source.find("#", pos);
	if(pos == std::string::npos)
	{
		return true;
	}
	return false;
}

std::string InfoServer::deleteSpases(std::string source)
{
	int i = 0;
	const char *str = source.c_str();
	if(str[source.length() - 1] == ';')
	{
		source.erase(source.find(";"), 1);
	}
	while(str[i] == ' ' || str[i] == '\t')
		i++;
	if(i)
		source.erase(0, i);
	return source;
}

void InfoServer::printInfoServer()
{
	std::cout << GREEN << "InfoServer" << END << std::endl;
	std::cout << BLUE << "Ip=" << END << ip << std::endl;
	std::cout << BLUE << "Port=" << END << port << std::endl;
	std::cout << BLUE << "Root=" << END << root<< std::endl;
	for(int i = 0; i < (int)methods.size(); i++)
	{
		std::cout << BLUE << i << "=" << END  <<methods[i]<< std::endl;
	}
	for(int i = 0; i < (int)locations.size(); i++)
	{
		std::cout << BLUE << i << "_loc " << END;
		locations[i].printLocation();
	}

}

void InfoServer::initSockAddrIn()
{
	memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(std::atoi(port.c_str()));
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

}

	void InfoServer::addLocation(Location location)
	{
		locations.push_back(location);
	}

std::string InfoServer::getPort() {
    return this->port;
}

