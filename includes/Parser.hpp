#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include "InfoServer.hpp"
#include "Location.hpp"

#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define END "\033[0m"

class Parser {
    std::vector<InfoServer> servers;
    std::vector<std::string> file;
    int index;
    std::string config_file_name;
    std::ifstream fin;
    std::string string_from_config_file;

    void errorConfigFile();

    void createInfoServer();

    bool createLocation(InfoServer &info_server);

    void readConfigFile();

    void foundInfoServers();

public:
    Parser(char *config_file_name);

    std::vector<InfoServer> parserConfigFile();

    void printServers();
};

#endif
