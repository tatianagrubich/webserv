#ifndef CGI_CPP
# define CGI_CPP

# include <iostream>
# include <string>
# include <map>
# include <vector>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../includes/Webserv.hpp"
# include "../includes/InfoServer.hpp"

#define BUFFER_SIZE 1024

extern char **envp; //устанавливается в сеттере через функцию setenv()

class Cgi {
    private:
        Location    _request_method;
        std::string _root;
        std::string _cgiPath;
        std::string _cgiResult;
    public:
        Cgi(Cgi const &);
        Cgi(std::vector<InfoServer> servers, char *const *buffer);

        ~Cgi();

        void setEnv(std::vector<InfoServer> servers, char *const *buffer);
        void cgiExec(std::vector<InfoServer> servers, char *const *buffer);
        std::string &getCgiRes();
};

#endif