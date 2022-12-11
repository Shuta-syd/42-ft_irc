# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 20:33:11 by shogura           #+#    #+#              #
#    Updated: 2022/12/11 15:52:44 by shogura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++

#CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MP -MMD -pedantic

SRCDIR = src
SRCS = $(shell find $(SRCDIR) -name "*.cpp" -type f)

OBJDIR = obj
OBJS = $(subst $(SRCDIR), ./$(OBJDIR), $(SRCS:%.cpp=%.o))

DEPSDIR = deps
DEPS = $(subst $(SRCDIR), ./$(DEPSDIR), $(SRCS:%.cpp=%.d))

DEPSFLAG = -MMD -MP -MF $(DEPSDIR)/$(*).d
DEBUGFLAG := -g3 -fsanitize=address

INC = inc

all: $(NAME)

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@mkdir -p $(DEPSDIR)
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
	$(RM) $(DEPS)
	$(RM) $(NAME)
	@$(RM) -rf $(OBJDIR)

fclean:clean

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)

run:
	./ircserv 8080 password

RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
