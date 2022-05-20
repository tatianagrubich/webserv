//
// Created by Iraida Kathrine on 5/10/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include <experimental/filesystem>

#include "Server.hpp"
#include "http_request.hpp"

//static std::string getDateTime() {
//    char buffer[100] = {0};
//    time_t current_time;
//    tm *current_tm;
//    time(&current_time);
//    current_tm = localtime(&current_time);
//    strftime(buffer, 100, "%T %d.%m.%Y", current_tm);
//    return std::string(buffer);
//}

static void *getInAddress(sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((sockaddr_in *) sa)->sin_addr);
    }
    return &(((sockaddr_in6 *) sa)->sin6_addr);
}

static std::string getIpAddress(const sockaddr_in &clients) {
    char ip[INET6_ADDRSTRLEN] = {0};
    inet_ntop(clients.sin_family, getInAddress((sockaddr * ) & clients), ip, sizeof ip);
    return std::string(ip);
}

void Server::clientProcessing(int socket_client, std::string ip) {
    char buffer[1024 * 16] = {0};
    int read_bytes = 0;
    (void) ip;

    read_bytes = read(socket_client, buffer, sizeof(buffer));
    //std::cout << "read_bytes = " << read_bytes << std::endl;
    if (read_bytes <= 0) {
        close(socket_client);
        return;
    }
    buffer[read_bytes] = '\0';

    http_request request;
    request.parserHttp(buffer);

    std::cout << "Connection from " << ip << " request url " << request.url() << std::endl;

    if (request.type() != http_request::enumType::GET || request.type() != http_request::enumType::POST || request.type() != http_request::enumType::PUT || request.type() != http_request::enumType::DELETE)
    {
        std::cout << "Unknown type of request. Not support!" << std::endl;
    }

    ++get_request_count;

    switch (request.url().length()) {
        case 1: // "/"
        {
            if (request.url() == "/") {
                std::stringstream response;
                response << "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-Type: text/html\r\nConnect-Length: "
                         << html_data.size() << "\r\n\r\n";

                int sended = 0;
                //status OK
                sended = write(socket_client, response.str().c_str(), response.str().length()); //for "HTTP/1.1 200 OK"

                if (sended > 0) {
                    //send index.html
                    sended = write(socket_client, html_data.data(), html_data.size());
                }
            }
            break;
        }
    }

}

Server::~Server() {}

Server::Server(int serverPort) : port(serverPort) {}

bool Server::serverStart() {
    if (!socketInit()) {
        std::cerr << "Socket init error" << std::endl;
        return false;
    }
    std::cout << "The server was started on the port " << port << std::endl;

    while (1) {
        int socket_client;
        sockaddr_in sa_client;
        socklen_t len_client = sizeof(sa_client);

        socket_client = accept(server_socket, (sockaddr * ) & sa_client, &len_client);
        if (socket_client == -1) {
            std::cerr << "Accept error" << std::endl;
            continue;
        }
        std::string ip = getIpAddress(sa_client);
        clientProcessing(socket_client, ip);
    }

    return true;
}

bool Server::socketInit() {
    server_socket = socket(PF_INET, SOCK_STREAM, 0); //AF_INET

    if (server_socket == -1) {
        std::cerr << "Can`t create socket" << std::endl;
        return false;
    }

    sockaddr_in sa_serv;
    memset(&sa_serv, 0, sizeof(sa_serv));
    sa_serv.sin_family = AF_INET;
    sa_serv.sin_addr.s_addr = INADDR_ANY;
    sa_serv.sin_port = htons(port);

    if (bind(server_socket, (sockaddr * ) & sa_serv, sizeof(sa_serv)) != 0) {
        std::cerr << "Socket can`t bind port " << port << std::endl;
        return false;
    }
    if (listen(server_socket, 37) != 0) {
        std::cerr << "Socket can`t configure listening port " << std::endl;
        return false;
    }
    return true;
}