NAME		= 	webserv
SRCS		= 	main.cpp \
				utils/utils_for_parser.cpp \
				src/InfoServer.cpp \
				src/Location.cpp \
				src/Parser.cpp
INCLUDES	=	includes/Webserv.hpp \
				includes/InfoServer.hpp \
				includes/Location.hpp \
				includes/Parser.hpp

CC 			= 	c++ -std=c++98
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
OBJS		=	$(SRCS:.cpp=.o)

.cpp.o:
	$(CC) $(FLAGS) -c $< -o $@

${NAME}: $(OBJS) $(INCLUDES)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)


all : $(NAME)

clean :
	$(RM) $(OBJS)


fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
