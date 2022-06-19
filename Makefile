# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vico <vico@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 18:15:11 by vico              #+#    #+#              #
#    Updated: 2022/06/16 00:44:45 by vico             ###   ########.fr        #
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

SRCSDIR		= srcs
BINDIR		= bin
INCSDIR		= includes

SRCS		= $(wildcard srcs/main.cpp srcs/Server.cpp srcs/utils.cpp srcs/Client.cpp)			
OBJS 		= $(patsubst $(SRCSDIR)/%.cpp,$(BINDIR)/%.o,$(SRCS))
DEPENDS 	= $(OBJS:%.o=%.d)
INCS		= -I $(INCSDIR)

NAME		= ircserv
CXX			= clang++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address
RM			= rm -rf

$(BINDIR)/%.o: $(SRCSDIR)/%.cpp
			@printf "$(BLUE)$< -> $(ORANGE)$@$(RESET)\n"
			@$(CXX) $(CXXFLAGS) -MMD -MP $(INCS) -c $< -o $@

$(NAME):	$(OBJS)
			@printf "\n$(BLUE)Compiling files...$(RESET)"
			@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
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