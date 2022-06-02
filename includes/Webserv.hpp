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
#include "../cgi/cgi.hpp"
#include "Server.hpp"
#include <cstdio>
#include <sys/stat.h>
#include <fcntl.h>

bool errorProgramName(const char *program_name);

std::string getFilesFromDirectory();

void deleteFile(std::string pathFile);

#endif
