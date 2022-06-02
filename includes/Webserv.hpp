#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <pthread.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include "InfoServer.hpp"
#include "Location.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "StartMultipleServers.hpp"

bool errorProgramName(const char *program_name);
std::string getFilesFromDirectory();

#endif
