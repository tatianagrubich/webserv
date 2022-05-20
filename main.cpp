//
// Created by Iraida Kathrine on 5/10/22.
//

#include <sstream>
#include <iostream>
#include "Server.hpp"

int main(int argc, char **argv) {
    int port = 0;

    if (argc >= 2) {
        port = std::stoi(argv[1]);
    } else {
        std::cerr << "Oops!! To many parameters.." << std::endl;
    }

    Server serv(port);
    if (!serv.serverStart()) {
        std::cerr << "Server can`t be start" << std::endl;
    }

    return 0;
}