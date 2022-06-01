//
// Created by Iraida Kathrine on 5/20/22.
//

#include <sstream>
#include "../includes/http_request.hpp"

http_request::http_request() {

}

void http_request::parserHttp(const char *adDataStr) {
    std::istringstream iss(adDataStr);
    std::string line;
    std::getline(iss, line);
//    std::cout << "line = " << line << std::endl;
    parserForRequest(line);

    std::string str;
    while (std::getline(iss, line)) { //add request body; now this method read ONLY request`s header (without body)
        std::istringstream iss_line(line);
        iss_line>>str;
//        std::cout << "str = " << str << std::endl;
    }
    str = "";
}

void http_request::parserForRequest(std::string &str) {
    m_type = Unknown;
//    std::string url;

    std::istringstream iss(str);
    std::string tempType;

    iss>>tempType;
    //iss>>m_url;
//    std::cout << "tempType = " << tempType << std::endl;
//    std::cout << "m_url = " << m_url << std::endl;

    switch (tempType.length()) {
        case 3: //GET, PUT
        {
            if (tempType == "GET") {
                m_type = GET;
                //std::cout << "request type = " << type() << std::endl;
            }
            break;
        }
        case 4: //POST
        {
            if (tempType == "POST") {
                m_type = POST;
                //std::cout << "request type = " << type() << std::endl;
            }
            break;
        }
        case 6: //DELETE
        {
            if (tempType == "DELETE") {
                m_type = DELETE;
                //std::cout << "request type = " << type() << std::endl;
            }
            break;
        }
    }
    iss>>m_url;
}

const s_enumType &http_request::type() const {
    return m_type;
}

const std::string &http_request::url() const {
    return m_url;
}