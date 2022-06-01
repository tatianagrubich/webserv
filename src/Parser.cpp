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
		std::size_t pos_server = 0;
		std::size_t pos_loc = 0;

		while (++index < (int)file.size())
    	{
			pos_server = 0;
			pos_loc = 0;
			if ((pos_server = file[index].find("server {", pos_server)) != std::string::npos)
				break;
			if ((pos_loc = file[index].find("location", pos_loc)) != std::string::npos)
			{
				while((pos_loc = file[index].find("location", pos_loc)) != std::string::npos)
				{
					// pos_server = 0;
					// if ((pos_server = file[index].find("server {", pos_server)) != std::string::npos)
					// 	return;

					if(!createLocation(info_server))
					{
						info_server.initSockAddrIn();
						servers.push_back(info_server);
						return;
					}
				}
			}
			info_server.parsingStringForInfoServer(file[index]);
			// info_server.printInfoServer();

    	}
		info_server.initSockAddrIn();
		servers.push_back(info_server);
	}

	bool Parser::createLocation(InfoServer &info_server)
	{
		Location location;
		std::size_t pos_loc = 0;
		std::size_t pos_serv = 0;

		location.parsingStringForLocation(file[index]);
		while (++index < (int)file.size())
    	{
			pos_loc = 0;
			pos_serv = 0;
			if ((pos_loc = file[index].find("location", pos_loc)) != std::string::npos)
				break;
			if ((pos_serv = file[index].find("server {", pos_serv)) != std::string::npos)
				return false;
			location.parsingStringForLocation(file[index]);

    	}
		info_server.addLocation(location);
		return true;
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
