//
// Created by Iraida Kathrine on 5/27/22.
//

#include "../includes/StartMultipleServers.hpp"

void StartMultipleServers::startMultipleServers(int socket_fd) {

    for (;;) {
        int fd, res;
        fd_set readfds, writefds;
        int max_ls = socket_fd;
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(max_ls, &readfds);

        for (std::vector<StartMultipleServers>::iterator it = ) {
            FD_SET(fd, &readfds);
            if (&readfds) {
                FD_SET(fd, &writefds);
            }
            if (fd > max_ls)
                max_ls = fd;
        }
        res = select(max_ls + 1, &readfds, &writefds, NULL, NULL);

    }
}