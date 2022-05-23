#include "../includes/Parser.hpp"


// 	InfoServer::~InfoServer(void)
// 	{

// 	}
// 	InfoServer::InfoServer(const InfoServer &other)
// 	{

// 	}
// 	InfoServer	&InfoServer::operator=(const InfoServer &other)
// 	{

// 	}

void Parser::errorConfigFile()
{
	std::size_t pos = 0;

	pos = config_file_name.find(".conf", pos);
	fin.open(config_file_name);
    if (!fin.is_open() || pos == std::string::npos || pos != config_file_name.length() - strlen(".conf"))
    {
        std::cerr << "The file " << config_file_name << " is not open\n";
        exit(-1);
    }
}


Parser::Parser(char *config_file_name)
{
	this->config_file_name = config_file_name;
	index = 0;
}

std::vector<InfoServer> Parser::parserConfigFile()
{
	std::string tmp;

	errorConfigFile();
	readConfigFile();
	foundInfoServers();
	return servers;
}

void Parser::readConfigFile()
{
	std::string tmp;

	while (!fin.eof())
    {
        tmp = "";
        std::getline(fin, tmp);
        file.push_back(tmp);
    }
	fin.close();
}

void Parser::foundInfoServers()
{
	std::size_t pos = 0;

	while ((pos = file[index].find("server {", pos)) != std::string::npos)
    {
		createInfoServer();
    }
}

	void Parser::createInfoServer()
	{
		InfoServer info_server;
		std::size_t pos = 0;

		while (++index < (int)file.size())
    	{
			pos = 0;
			if ((pos = file[index].find("server {", pos)) != std::string::npos)
				break;
			info_server.parsingStringForInfoServer(file[index]);

    	}
		info_server.initSockAddrIn();
		servers.push_back(info_server);
	}

	void Parser::printServers()
	{
		std::cout <<BLUE << "PRINT_SERVICES" << END << std::endl;;
		for(int i = 0; i < (int)servers.size(); i++)
		{
			std::cout << i << " ";
			servers[i].printInfoServer();
		}
	}
