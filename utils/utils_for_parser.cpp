#include "../includes/Webserv.hpp"

bool errorProgramName(const char *program_name)
{
	return strcmp("./webserv", program_name) ? false : true;
}






