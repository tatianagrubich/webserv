#include "../includes/Location.hpp"

// InfoServer::InfoServer(void)
// {

// }
// 	InfoServer::~InfoServer(void)
// 	{

// 	}
// 	InfoServer::InfoServer(const InfoServer &other)
// 	{

// 	}
// 	InfoServer	&InfoServer::operator=(const InfoServer &other)
// 	{

// 	}

void Location::parsingStringForLocation(std::string source)
{
	foundParametrsForLocation(source);
	if(parameters.path != std::string::npos)
	{
		parsingPath(source);
	}
	else if (parameters.methods != std::string::npos)
	{
		parsingMethods(source);
	}
	else if (parameters.root != std::string::npos)
	{
		parsingRoot(source);
	}
	else if (parameters.index != std::string::npos)
	{
		parsingIndex(source);
	}
	}

void Location::foundParametrsForLocation(std::string source)
{
	parameters.path = source.find("location");
	parameters.methods = source.find("methods");
	parameters.root = source.find("root");
	parameters.index = source.find("index");
}

void Location::parsingPath(std::string source)
{
	if(!isComment(source))
	{
		return ;
	}
	source.erase(parameters.path, strlen("location"));
	source = deleteSpases(source);
	path = source;
}

void Location::parsingMethods(std::string source)
{
	if(!isComment(source))
	{
		return ;
	}
	source.erase(parameters.methods, strlen("methods"));
	source = deleteSpases(source);

	std::size_t pos = 0;
	std::size_t next = 0;

	while((next = source.find(" ", pos)) != std::string::npos)
	{
		methods.push_back(source.substr(pos, next - pos));
		pos = next + 1;
	}
	methods.push_back(source.substr(pos, next - pos));
	std::cout << methods.size() << std::endl;
	}

void Location::parsingRoot(std::string source)
{
	if(!isComment(source))
	{
		return ;
	}
	source.erase(parameters.root, strlen("root"));
	source = deleteSpases(source);
	root = source;
}

void Location::parsingIndex(std::string source)
{
	if(!isComment(source))
	{
		return ;
	}
	source.erase(parameters.index, strlen("index"));
	source = deleteSpases(source);
	index = source;
}

bool Location::isComment(std::string source)
{
	std::size_t pos = 0;

	pos = source.find("#", pos);
	if(pos == std::string::npos)
	{
		return true;
	}
	return false;
}

std::string Location::deleteSpases(std::string source)
{
	int i = 0;
	const char *str = source.c_str();
	if(str[source.length() - 1] == ';')
	{
		source.erase(source.find(";"), 1);
	}
	else if(str[source.length() - 1] == '{')
	{
		source.erase(source.find("{"), 1);
	}
	while(str[i] == ' ' || str[i] == '\t')
		i++;
	if(i)
		source.erase(0, i);
	i = 0;
	while(str[i] != ' ' && str[i] != '\t')
		i++;
	if(i < (int)source.length())
		source.erase(i, source.length() - i);
	return source;
}

void Location::printLocation()
{
	std::cout << GREEN << "InfoLocation" << END << std::endl;
	std::cout << BLUE << "Path=" << END << path<< std::endl;
	std::cout << BLUE << "Root=" << END << root<< std::endl;
	std::cout << BLUE << "Index=" << END << index << std::endl;
	for(int i = 0; i < (int)methods.size(); i++)
	{
		std::cout << BLUE << i << "_loc=" << END  << methods[i]<< std::endl;
	}
}
