#include "../includes/Webserv.hpp"

bool errorProgramName(const char *program_name)
{
	return strcmp("./webserv", program_name) ? false : true;
}

std::string getFilesFromDirectory()
{
    DIR *dir = opendir("./files");
    std::string result = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>WEBSERV</title>\n<link rel=\"shortcut icon\" href=\"../icons/favicon.png\" type =\"image/png\">\n</head>\n<body>\n";
    std::string tmp;
    if (dir)
    {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL)
        {
            result += "<div>";
            result += "<a href=\"";
            result += ent->d_name;
            result += "\">";
            result += ent->d_name;
            result += "</a>\n";
            result += "</div>";
        }
    }
    else
    {
        fprintf(stderr, "Error opening directory\n");
        exit(-1);
    }
    result += "</body>\n</html>";
    return result;
}