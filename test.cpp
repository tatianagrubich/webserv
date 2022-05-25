#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CONNECTIONS 1000

int create_socket(const char *apstrPort) {
    int sock;
    // struct socketaddr_in addr;
    struct addrinfo hints;
    struct addrinfo *serverinfo;
    struct addrinfo *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //неважно, IPv4 или IPv6 (AF_INET = IPv4, AF_INET6 = IPv6)
    hints.ai_socktype = SOCK_STREAM; // сокет потока
    hints.ai_flags = AI_PASSIVE; // чтобы IP-адрес заполнялся автоматом

    int res = getaddrinfo(NULL, apstrPort, &hints, &serverinfo); //функция запрещена
    if (res != 0) {
        std::cerr << "getaddrinfo() error\n";
        return (-1);
    }
    for (p = serverinfo; p != NULL; p = p->ai_next) {
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol); //создаем сокет
        if (sock == -1)
            continue;
        /*
          * Установить флаги на сокете.
          * int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
          * SOL_SOCKET - установить параметр на уровне сокета
          * SO_REUSEADDR - разрешать повторное использование локальных адресов, если это поддерживается протоколом. Эта опция принимает значение типа int . Это булева опция
         */
        int opt = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) ==
            -1) //разрешена, если сокет занят перезапустить и его можно использовать
        {
            std::cerr << "error setsockopt()\n";
            close(sock);
            freeaddrinfo(serverinfo);
            return (-2);
        }

        if (bind(sock, p->ai_addr, p->ai_addrlen) == -1) // связываем IP и порт
        {
            close(sock);
            continue;
        }
        break;
    }

    freeaddrinfo(serverinfo);

    if (p == NULL) {
        std::cerr << "error server\n";
        return (-3);
    }

    if (listen(sock, MAX_CONNECTIONS) == -1) {
        std::cerr << "error listen()\n";  //подготавливает сокет для соединения
        return (-4);
    }

    return sock;
}

void *get_client_addr(struct sockaddr *sa)
{
    if(sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void http_request(int aSock)
{
    const int request_buffer_size = 65536;
    char request[request_buffer_size];
    int bytes_recvd = recv(aSock, request, request_buffer_size - 1, 0);
    if (bytes_recvd < 0)
    {
        std::cerr << "error recv()\n";  //подготавливает сокет для соединения
        return;
    }
    request[bytes_recvd] = '\0';
    std::cout << request;


}



int main() {
    int sock;
    sock = create_socket("8000");
    std::cout << "socket = " << sock << std::endl;
    if (sock < 0)
    {
        std::cerr << "error create_socket()\n";  //подготавливает сокет для соединения
        return (-1);
    }
    std::cout << "server create" << std::endl;

    struct sockaddr_storage client_addr;
    int client_d;
    while(1)
    {
        socklen_t s_size = sizeof(client_addr);
        std::cout << "1\n";
        client_d = accept(sock, (struct sockaddr *)&client_addr, &s_size);
        std::cout << "2\n";
        if (client_d == -1)
        {
            std::cerr << "error accept()\n";  //подготавливает сокет для соединения
            return (-2);
        }
        std::cout << "client_d = " << client_d << std::endl;
        char ip[INET6_ADDRSTRLEN];
        inet_ntop(client_addr.ss_family, get_client_addr((struct sockaddr *)&client_addr), ip, sizeof(ip));
        std::cout << "server: got connection from " << ip << std::endl;

        http_request(client_d);
       close(client_d);
    }



    return 0;
}
