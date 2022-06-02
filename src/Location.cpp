#include "../includes/Location.hpp"

void Location::parsingStringForLocation(std::string source)
{
	foundParametrsForLocation(source);
	if (parameters.path != std::string::npos)
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
	else if (parameters.cgi != std::string::npos)
	{
		parsingCgi(source);
	}
}

void Location::foundParametrsForLocation(std::string source)
{
	parameters.path = source.find("location");
	parameters.methods = source.find("methods");
	parameters.root = source.find("root");
	parameters.cgi = source.find("cgi");
	parameters.index = source.find("index");
}

void Location::parsingPath(std::string source)
{
	if (!isComment(source))
	{
		return;
	}
	source.erase(parameters.path, strlen("location"));
	source = deleteSpases(source);
	path = source;
}

void Location::parsingMethods(std::string source)
{

	if (!isComment(source))
	{
		return;
	}
	source.erase(parameters.methods, strlen("methods"));
	source = deleteSpases(source);
	std::size_t pos = 0;
	std::size_t next = 0;

	while ((next = source.find(" ", pos)) != std::string::npos)
	{
		methods.push_back(source.substr(pos, next - pos));
		pos = next + 1;
	}
	methods.push_back(source.substr(pos, next - pos));
}

void Location::parsingRoot(std::string source)
{
	if (!isComment(source))
	{
		return;
	}
	source.erase(parameters.root, strlen("root"));
	source = deleteSpases(source);
	root = source;
}

void Location::parsingIndex(std::string source)
{
	if (!isComment(source))
	{
		return;
	}
	source.erase(parameters.index, strlen("index"));
	source = deleteSpases(source);
	index = source;
}

void Location::parsingCgi(std::string source)
{
	std::cout << source << std::endl;
	if (!isComment(source))
	{
		return;
	}
	source.erase(parameters.cgi, strlen("cgi"));
	source = deleteSpases(source);
	pathCgi = source;
}

bool Location::isComment(std::string source)
{
	std::size_t pos = 0;

	pos = source.find("#", pos);
	if (pos == std::string::npos)
	{
		return true;
	}
	return false;
}

std::string Location::deleteSpases(std::string source)
{
	int i = 0;
	const char *str = source.c_str();
	if (str[source.length() - 1] == ';')
	{
		source.erase(source.find(";"), 1);
	}
	else if (str[source.length() - 1] == '{')
	{
		source.erase(source.find("{"), 1);
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (i)
		source.erase(0, i);
	i = source.length() - 1;
	int a = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i--;
		a++;
	}
	if (a)
		source.erase(i + 1, a);

	return source;
}

void Location::printLocation()
{
	std::cout << GREEN << "InfoLocation" << END << std::endl;
	std::cout << BLUE << "Path=" << END << path << std::endl;
	std::cout << BLUE << "Root=" << END << root << std::endl;
	std::cout << BLUE << "Index=" << END << index << std::endl;
	std::cout << BLUE << "pathCgi=" << END << pathCgi << std::endl;
	for (int i = 0; i < (int)methods.size(); i++)
	{
		std::cout << BLUE << i << "_loc_meth=" << END << methods[i] << std::endl;
	}
}

std::string Location::getRoot()
{
	return this->root;
}

std::string Location::getIndex()
{
	return this->index;
}

std::string Location::getPath()
{
	return this->path;
}

std::string Location::getPathCgi()
{
	return this->pathCgi;
}

std::vector<std::string> Location::getMethods()
{
	return this->methods;
}
