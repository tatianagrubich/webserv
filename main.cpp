#include "includes/Webserv.hpp"

int port;
int server_socket;
int yes;
Server serv;

int main(int argc, char **argv) {
    if (argc != 2 || !errorProgramName(argv[0])) {
        std::cerr << "Error argument" << std::endl;
        return (-1);
    }
    Parser parser(argv[1]);
    std::vector<InfoServer> servers = parser.parserConfigFile();
    parser.printServers();

//    for (unsigned long i = 0; i < servers.size(); i++) {
//        int port = std::stoi(servers[i].getPort());
//        Server serv(port);
//        if (!serv.serverStart()) {
//            std::cerr << "Server can`t be start" << std::endl;
//        }
////        close(serv.getSocket());
//    }

//    fd_set read_fds;
//
//    FD_ZERO(&read_fds);


    int mass[servers.size()];
    int port[servers.size()];
    for (unsigned long i = 0; i < servers.size(); i++) {
        mass[i] = socket(AF_INET, SOCK_STREAM, 0);
//        FD_SET(mass[i], &read_fds);
        //fdmax = mass[i];
       // std::cout << "mass[i] = " << mass[i] << std::endl;
        port[i] = std::stoi(servers[i].getPort());
        //std::cout << "port[i] = " << port[i] << std::endl;
    }

    std::vector<Server> serv;
    for (unsigned long i = 0; i < servers.size(); i++) {
        Server servers(port[i]);
        serv.push_back(servers);
    }

    for (unsigned long i = 0; i < servers.size(); i++) {
//        FD_ISSET(i, &read_fds);
        serv[i].serverStart(mass[i]);
//        std::thread t1(serv[i].serverStart(mass[i]));
//        t1.join();

        //Server serv(port[i]);
//        serv[i].serverStart(mass[i]);
//        if (!serv.serverStart(mass[i])) {
//            std::cerr << "Server can`t be start" << std::endl;
//        }
    }


    return (0);
}