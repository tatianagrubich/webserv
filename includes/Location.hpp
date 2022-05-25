#ifndef LOCATION_HPP
# define LOCATION_HPP
# include <iostream>
# include <vector>

#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define END "\033[0m"

typedef struct s_loc
{
	std::size_t path;
	std::size_t methods;
	std::size_t root;
	std::size_t index;
} t_loc;

class Location
{
	std::string					path;
	std::string					root;
	std::string					index;
	std::vector<std::string>	methods;
	t_loc						parameters;
	// static const int	bits = 8;

	void foundParametrsForLocation(std::string source);
	std::string deleteSpases(std::string source);
	bool isComment(std::string source);
	void parsingPath(std::string source);
	void parsingMethods(std::string source);
	void parsingRoot(std::string source);
	void parsingIndex(std::string source);

public:
	// InfoServer(void);
	// ~InfoServer(void);
	// InfoServer(const InfoServer &other);
	// InfoServer	&operator=(const InfoServer &other);
	void parsingStringForLocation(std::string source);
	void printLocation();
};

#endif
