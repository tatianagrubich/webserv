#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <thread>
#include <pthread.h>
# include "InfoServer.hpp"
# include "Location.hpp"
# include "Parser.hpp"
# include "Server.hpp"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

#define CGI = 0

bool errorProgramName(const char *program_name);
// std::vector<InfoServer> parserConfigFile(const char *config_file_name);
// void deleteSpases(std::string source);
std::string getFilesFromDirectory();


#endif
