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
#include <fstream>
#include <experimental/filesystem>
#include <filesystem>

#include "Server.hpp"
#include "http_request.hpp"

//namespace fs = std::experimental::filesystem;
//namespace bfs = boost::filesystem;

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
    //(void) ip;

    read_bytes = read(socket_client, buffer, sizeof(buffer));
    //std::cout << "read_bytes = " << read_bytes << std::endl;
    if (read_bytes <= 0) {
        close(socket_client);
        return;
    }
    buffer[read_bytes] = '\0';

    http_request request;
    request.parserHttp(buffer);

    std::cout << buffer << std::endl;

    std::cout << "Connection from " << ip << " request url " << request.url() << std::endl;

    if (request.type() != GET && request.type() != POST && request.type() != PUT && request.type() != DELETE)
    {
        std::cout << "Unknown type of request. Not support!" << std::endl;
        return ;
    }

    ++get_request_count;
    //html_data = "index.html";

    switch (request.url().length()) {
        case 1: // "/"
        {
            if (request.url() == "/") {
                std::stringstream response;
                response << "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-Type: text/html\r\nConnect-Length: "
                         << html_data.size() << "\r\n\r\n";

                int sended = 0;
                //status OK
                std::cout << "socket_client = " << socket_client << std::endl;
                sended = write(socket_client, response.str().c_str(), response.str().length()); //for "HTTP/1.1 200 OK"

                if (sended > 0) {
                    //send index.html
                    sended = write(socket_client, html_data.data(), html_data.size());
                    //std::cout << "html_data.data() = " << html_data << std::endl;
                }
            }
            break ;
        }
        case 12: //"/favicon.ico"
        {
            if (request.url() == "/favicon.ico")
            {
                std::stringstream response;
                response << "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-Type: image/png\r\nConnect-Length: "
                         << fav_icon_buffer.size() << "\r\n\r\n";
                int sended = 0;
                //status OK
                sended = write(socket_client, response.str().c_str(), response.str().length()); //for "HTTP/1.1 200 OK"

                if (sended > 0) {
                    //send image.png
                    sended = write(socket_client, fav_icon_buffer.data(), fav_icon_buffer.size());
                    //std::cout << "fav_icon_buffer.data() = " << fav_icon_buffer.data() << std::endl;
                }

            }
            break ;
        }
    }
}

Server::~Server() {
}

Server::Server(int serverPort) : port(serverPort) {}

bool Server::serverStart() {

    //TODO:!!!!!

    std::ifstream html_file;
    std::string path_res = "html_data/index.html";
    html_file.open(path_res.c_str(), std::ios::binary | std::ios::ate);

    if (!html_file.is_open())
    {
        std::cerr << "Html file did not opened!! Path = " << path_res << std::endl;
        return false;
    }

    html_data.reserve(html_file.tellg());
    html_file.seekg(0, std::ios::beg);


//    int size = html_file.tellg();
//    char *bufff = new char [size];
//    html_file.read(bufff, size);

    html_data.assign((std::istreambuf_iterator<char>(html_file)), std::istreambuf_iterator<char>());


    //std::cout << "html_data = " << html_data << std::endl;
    html_file.close();


    std::ifstream icon_file;
    std::string path_icon = "icons/favicon.png";
    icon_file.open(path_icon.c_str(), std::ios::binary | std::ios::ate);
    if (!icon_file.is_open())
    {
        std::cerr << "Favicon file did not opened! Path = " << path_icon.c_str() << std::endl;
    }
    std::streamsize  size = icon_file.tellg();
    fav_icon_buffer.resize(size);
    icon_file.seekg(0, std::ios::beg);

    if (!icon_file.read(fav_icon_buffer.data(), size))
    {
        std::cerr << "Favicon read error" << std::endl;
    }
    icon_file.close();




//    std::filesystem::path html_file_path = std::filesystem::current_path() / "html_data" / "index.html";
//    html_file.open(html_file_path.c_str(), std::ios::binary | std::ios::ate);
//
//    if (!html_file.is_open())
//    {
//        std::cerr << "Html file didn`t opened!! Path = " << html_file_path.c_str() << std::endl;
//        return false;
//    }
//
//    html_data.reserve(html_file.tellg());
//    html_file.seekg(0, std::ios::beg);
//    html_data.assign((std::istreambuf_iterator<char>(html_file)), std::istreambuf_iterator<char>());
//    html_file.close();
//
//    std::ifstream icon_file;
//    bfs::path path_icon_file = bfs::current_path() / "icons" / "favicon.png";
//    icon_file.open(path_icon_file.c_str(), std::ios::binary | std::ios::ate);
//
//    if (!icon_file.is_open())
//    {
//        std::cerr << "Favicon file did not opened! Path = " << path_icon_file.c_str() << std::endl;
//    }
//
//    std::streamsize  size = icon_file.tellg();
//    fav_icon_buffer.resize(size);
//    icon_file.seekg(0, std::ios::beg);
//
//    if (!icon_file.read(fav_icon_buffer.data(), size))
//    {
//        std::cerr << "Favicon read error" << std::endl;
//    }
//    icon_file.close();


    if (!socketInit()) {
        std::cerr << "Socket init error" << std::endl;
        return false;
    }
    std::cout << "The server was started on the port " << port << std::endl;

    while (1) {
        int socket_client;
        sockaddr_in sa_client;
        socklen_t len_client = sizeof(sa_client);

        socket_client = accept(server_socket, (sockaddr *) & sa_client, &len_client);
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
    server_socket = socket(AF_INET, SOCK_STREAM, 0); //AF_INET

    std::cout << "server_socket = " << server_socket << std::endl;

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