NAME		= CPU
SRCS		= $(shell find "." -name "*.cpp")
OBJS		= $(SRCS:.cpp=.o)
CXXFLAGS	= -Wall -Werror -Wextra -std=c++11
RM			= rm -rf
CXX			= g++

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $(<:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) Created!$(DEFAULT)"

clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)Object Files Deleted!$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)All Deleted!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
