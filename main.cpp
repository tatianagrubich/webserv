#include "includes/Webserv.hpp"

int main(int argc, char **argv) {
    if (argc != 2 || !errorProgramName(argv[0])) {
        std::cerr << "Error argument" << std::endl;
        return (-1);
    }
    Parser parser(argv[1]);
    std::vector<InfoServer> servers = parser.parserConfigFile();
    parser.printServers();

    for (unsigned long i = 0; i < servers.size(); i++) {
        int port = std::stoi(servers[i].getPort());
        Server serv(port);
        if (!serv.serverStart(servers)) {
            std::cerr << "Server can`t be start" << std::endl;
        }
    }
    return (0);
}
