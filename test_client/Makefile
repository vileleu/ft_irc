# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vico <vico@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 12:08:54 by vico              #+#    #+#              #
#    Updated: 2022/03/10 13:46:58 by vico             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE = 		\033[0;34m
GREEN = 	\033[0;32m
LIGHTBLUE = \033[1;34m
RED = 		\033[0;31m
YELLOW = 	\033[1;33m
ORANGE = 	\033[0;33m
MAGENTA = 	\033[0;35m
RESET = 	\033[0m

SRCS		= $(wildcard client.cpp)

OBJS		= $(SRCS:.cpp=.o)

NAME		= client

HEADERS		= -I .

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address

%.o: %.cpp
			@clang++ $(CXXFLAGS) $(HEADERS) -c -o $@ $<

$(NAME):	$(OBJS)
			@printf "\n$(BLUE)Compiling files..."
			@clang++ $(CXXFLAGS) $(OBJS) $(HEADERS) -o $(NAME)
			@printf "$(GREEN)[$(NAME) done][✔]$(RESET)\n"

all:		 $(NAME)

clean:
			@printf "\n$(RED)Erase files '.o'\n"
			@rm -rf $(OBJS)
			@printf "$(RESET)\n"

fclean:
			@printf "\n$(RED)Erase files '.o'\n"
			@rm -rf $(OBJS)
			@printf "$(RED)Delete executable file\n"
			@rm -rf $(NAME)
			@printf "$(RESET)\n"

re:			fclean all

.PHONY:		clean fclean re all