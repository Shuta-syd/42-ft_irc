# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 20:33:11 by shogura           #+#    #+#              #
#    Updated: 2022/11/24 15:09:37 by shogura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++

#CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MP -MMD -pedantic

SRCDIR = .
SRCS = $(shell find $(SRCDIR) -name "*.cpp" -type f)

OBJDIR = .
OBJS = $(SRCS:%.cpp=%.o)

DEPS    =    $(SRCS:%.cpp=%.d)

INC = inc

RM = rm -rf

all: $(NAME)

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -I$(INC) -o $@ -c $<
	@echo "$< =========> $(GRN) $@ $(RES)"

$(NAME):$(OBJS)
	@$(CXX) $(CXXFLAGS) -I$(INC) -o $(NAME) $(OBJS)
	@echo "$(CYN)\n=====link=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(OBJS)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)$(NAME)$(RES)"
	@echo "$(CYN)==============$(RES)"


clean:
	$(RM) $(OBJS)
	$(RM) $(NAME)

fclean:clean

re: fclean all

.PHONY: all clean fclean re

-include obj/$(DEPS)

RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
