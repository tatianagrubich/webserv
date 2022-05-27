//
// Created by Iraida Kathrine on 5/10/22.
//

#ifndef WEBSERV_SERVER_H
#define WEBSERV_SERVER_H

#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include "InfoServer.hpp"

class Server {
private:
    int port;
    int server_socket; //socket fd
    InfoServer info;

    std::string html_data; //to load a html-page
    std::string start_date_time; //server start time
    size_t get_request_count;

    std::vector<char> fav_icon_buffer;

    bool socketInit();
    void clientProcessing(int, std::string);

public:
    Server(int server_port);
    ~Server();
    Server &operator=(Server const &other);
    Server(Server const &other);
    Server(int const &port, int const &server_socket);

//    TODO:!!!
//    void setServerPort(int port);
//    void setServerSocket(int server_socket);

    bool serverStart();
    void freeServerInfo(sockaddr_in &sa_serv);
};


#endif //WEBSERV_SERVER_H
