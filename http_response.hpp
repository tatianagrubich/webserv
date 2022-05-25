//
// Created by Iraida Kathrine on 5/25/22.
//

#ifndef WEBSERV_HTTP_RESPONSE_H
#define WEBSERV_HTTP_RESPONSE_H

#include <iostream>
#include <string>

class http_response {
private:
    std::string response_body;
public:
    http_response();
    ~http_response();
    void printResponse();
};


#endif //WEBSERV_HTTP_RESPONSE_H
