# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vico <vico@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 12:08:54 by vico              #+#    #+#              #
#    Updated: 2022/06/05 19:00:08 by vico             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE		= \033[0;34m
GREEN		= \033[0;32m
LIGHTBLUE	= \033[1;34m
RED			= \033[0;31m
YELLOW		= \033[1;33m
ORANGE		= \033[0;33m
MAGENTA		= \033[0;35m
RESET		= \033[0m

SRCS		= $(wildcard srcs/main.cpp)

OBJS 		= $(SRCS:%.cpp=%.o)

DEPENDS 	= $(SRCS:%.cpp=%.d)

INCLUDES	= -I./includes

NAME		= ft_irc

CXX			= c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address

RM			= rm -rf

%.o: %.cpp
			@printf "$(BLUE)$< -> $(ORANGE)$@$(RESET)\n"
			@$(CXX) $(CXXFLAGS) -MMD -MP $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			@printf "\n$(BLUE)Compiling files..."
			@$(CXX) $(CXXFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)
			@printf "$(GREEN)[$(NAME) done][✔]$(RESET)\n"

all:		 $(NAME)

clean:
			@printf "\n$(RED)Erase files '.o'\n"
			@$(RM) $(OBJS)
			@$(RM) $(DEPENDS)
			@printf "$(RESET)"

fclean:		clean
			@printf "$(RED)Delete executable file\n"
			@$(RM) $(NAME)
			@printf "$(RESET)\n"

re:			fclean all

.PHONY:		clean fclean re all