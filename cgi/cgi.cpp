#include "cgi.hpp"

Cgi::Cgi(Cgi const &cgi) : _request_method(cgi._request_method) { *this = cgi; }

Cgi::Cgi(std::vector<InfoServer> servers, char *const *buffer) {
	_root = servers[0].getLocations()[1].getRoot().c_str();
	_cgiPath = servers[0].getLocations()[1].getPathCgi().c_str();
	if (access(_cgiPath.c_str(), F_OK) == -1)
		throw std::runtime_error(": No such file or directory {" + _cgiPath + '}');
	if (access(_cgiPath.c_str(), X_OK) == -1)
		throw std::runtime_error(": " + _cgiPath + ": Permission denied.");
	this->setEnv(servers, buffer);
	this->cgiExec(servers, buffer);
}


Cgi::~Cgi() {}

void Cgi::setEnv(std::vector<InfoServer> servers, char *const *buffer) {
    setenv("REQUEST_METHOD", servers[0].getLocations()[1].getMethods()[0].c_str(), 1);
	setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
	setenv("PATH_INFO", servers[0].getLocations()[1].getPathCgi().c_str(), 1);
	setenv("QUERY_STRING", buffer, 1);
	setenv("SERVER_SOFTWARE", "webserv", 1);
	setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
	setenv("DOCUMENT_ROOT", _root.c_str(), 1);
	setenv("SCRIPT_NAME", "cgi_tester", 1);
	setenv("SCRIPT_FILENAME", "./cgi_tester", 1);
}


void    Cgi::cgiExec(std::vector<InfoServer> servers, char *const *buffer) {
    char const *args[3];
    int fd_write[2];
    int fd_read[2];
    char buff[BUFFER_SIZE + 1];
    int readBytes = 0;

    args[0] = _cgiPath.c_str();
	args[1] = getenv("SCRIPT_FILENAME");
	args[2] = NULL;
    if (pipe(fd_write) < 0 || pipe(fd_write) > 0)
        throw std::runtime_error("pipe() failed.");
    pid_t pid = fork();
    if (pid < 0)
        throw std::runtime_error("fork() failed.");
   if (pid == 0) {
        dup2(fd_write[0], STDERR_FILENO);
        close(fd_write[1]);
        dup2(fd_read[1], STDERR_FILENO);
        close(fd_read[0]);
        chdir(_root.c_str());
        if (execve(_cgiPath.c_str(), (char *const *)args, envp) == -1)
            exit (1);
    } else {
        close(fd_read[1]);
        close(fd_write[0]);
        write(fd_write[1], buffer, BUFFER_SIZE);
        bzero(buff, BUFFER_SIZE);
        while ((readBytes = read(fd_read[0], buff, BUFFER_SIZE)) > 0) {
            buff[readBytes] = '\0';
            _cgiResult.append(buff, readBytes);
        }
        close(fd_read[0]);
        wait(0);
    }
}