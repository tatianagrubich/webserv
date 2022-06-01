//
// Created by Iraida Kathrine on 5/20/22.
//

#ifndef WEBSERV_HTTP_REQUEST_H
#define WEBSERV_HTTP_REQUEST_H

#include <iostream>
#include <string>

//GET (request`s type) / (path)

typedef enum t_enumType {
    Unknown = 0,
    GET,
    POST,
    DELETE
}               s_enumType;

class http_request {
public:
    http_request();

    void parserHttp(const char*);
    const s_enumType &type() const;
    const std::string &url() const;
private:
    void parserForRequest(std::string &);

    s_enumType m_type;
    std::string m_url;
};


#endif //WEBSERV_HTTP_REQUEST_H
