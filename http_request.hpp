//
// Created by Iraida Kathrine on 5/20/22.
//

#ifndef WEBSERV_HTTP_REQUEST_H
#define WEBSERV_HTTP_REQUEST_H

//#define UNKNOWN 0;
//#define GET
//#define PUT
//#define POST
//#define DELETE

#include <iostream>
#include <string>

//GET (request`s type) / (path)

class http_request {
public:
    enum class enumType {
        Unknown = 0,
        GET,
        PUT,
        POST,
        DELETE
    };
public:
    http_request();

    void parserHttp(const char*);
    const enumType &type() const;
    const std::string &url() const;
private:
    void parserForRequest(std::string &);

    enumType m_type {enumType::Unknown};
    std::string m_url;
};


#endif //WEBSERV_HTTP_REQUEST_H
