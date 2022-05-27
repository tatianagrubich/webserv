#include "includes/Webserv.hpp"

int main(int argc, char **argv)
{
	if (argc != 2 || !errorProgramName(argv[0]))
	{
		std::cerr << "Error argument" << std::endl;
		return (-1);
	}
	Parser parser(argv[1]);
	std::vector<InfoServer> servers = parser.parserConfigFile();
	parser.printServers();

    int port = std::stoi(servers[0].getPort());
    //int port2 = std::stoi(servers[1].getPort());
    Server serv(port);
    //Server serv2(port2);
     if (!serv.serverStart()) {
         std::cerr << "Server can`t be start" << std::endl;
     }

	return (0);
}

/*
Lena
*/

// int main(int argc, char **argv)
// {
// 	if (argc != 2 || !errorProgramName(argv[0]))
// 	{
// 		std::cerr << "Error argument" << std::endl;
// 		return (-1);
// 	}
// 	Parser parser(argv[1]);
// 	std::vector<InfoServer> servers = parser.parserConfigFile();
// 	parser.printServers();



// 	return (0);
// }

/*
Tanya
*/

// #include <sstream>
// #include <iostream>
// #include "Server.hpp"

// int main(int argc, char **argv) {
//     int port = 0;

//     if (argc >= 2) {
//         port = std::stoi(argv[1]);
//     } else {
//         std::cerr << "Oops!! To many parameters.." << std::endl;
//         return 0;
//     }

//     Server serv(port);
//     if (!serv.serverStart()) {
//         std::cerr << "Server can`t be start" << std::endl;
//     }

//     return 0;
// }

