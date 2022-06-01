//
// Created by Iraida Kathrine on 5/27/22.
//

#ifndef WEBSERV_MAIN_STARTMULTIPLESERVERS_H
#define WEBSERV_MAIN_STARTMULTIPLESERVERS_H

#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>

class StartMultipleServers {
public:
    StartMultipleServers();
    ~StartMultipleServers();

    void startMultipleServers(int socket_fd);
};


#endif //WEBSERV_MAIN_STARTMULTIPLESERVERS_H
