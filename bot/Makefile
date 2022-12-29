NAME := ircbot
CXX := c++
RM := rm -rf

srcs := main.cpp BotReply.cpp Bot.cpp Utils.cpp

objs := $(srcs:%.cpp=%.o)
deps := $(srcs:%.cpp=%.d)

debugflags := -g3 -fsanitize=address
headerflags := -MMD -MP
CXXFLAGS := #-Wall -Werror -Wextra -std=c++98 -pedantic

############# basic rules ##############
.PHONY: all clean fclean re
all: $(NAME)

-include $(deps)

$(NAME): $(objs)
	@$(CXX) $(CXXFLAGS) $(objs) -o $(NAME)
	@echo "$(CYN)\n=====link=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(objs)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)$(NAME)$(RES)"
	@echo "$(CYN)==============$(RES)"

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -I. -o $(@) -c $(<)
	@echo "$< =========> $(GRN) $@ $(RES)"

clean:
	$(RM) $(objs)
	$(RM) $(deps)

fclean: clean
	$(RM) $(NAME)
	$(RM) *.o
	$(RM) *.d

re: fclean all

############## convenient rules ##############
.PHONY: debug leak
debug: CXXFLAGS += $(debugflags)
debug: re

run: all
	./ircbot 8080 password 42
RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
