//
// Created by Iraida Kathrine on 5/20/22.
//

#include <sstream>
#include "http_request.hpp"

http_request::http_request() {

}

void http_request::parserHttp(const char *adDataStr) {
    std::istringstream iss(adDataStr);
    std::string line;
    std::getline(iss, line);
    parserForRequest(line);

    std::string str;
    while (std::getline(iss, line)) { //add request body; now this method read ONLY request (without body)
        std::istringstream iss_line(line);
        iss_line>>str;
    }
    str = "";
}

void http_request::parserForRequest(std::string &str) {
    m_type = enumType::Unknown;

    std::istringstream iss(str);
    std::string tempType;

    iss>>tempType;

    switch (tempType.length()) {
        case 3: //GET, PUT
        {
            if (tempType == "GET")
                m_type = enumType::GET;
            else if (tempType == "PUT")
                m_type = enumType::PUT;
            break;
        }
        case 4: //POST
        {
            if (tempType == "POST")
                m_type = enumType::POST;
            break;
        }
        case 6: //DELETE
        {
            if (tempType == "DELETE")
                m_type = enumType::DELETE;
            break;
        }
    }
    iss>>m_url;
}

const http_request::enumType &http_request::type() const {
    return m_type;
}

const std::string &http_request::url() const {
    return m_url;
}