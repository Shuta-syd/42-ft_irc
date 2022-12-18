NAME := ircserv
CXXFLAGS := c++
RM := rm -rf

OBJS_DIR += srcs/
DEPS_DIR += srcs/
srcs += $(addprefix srcs/, \
    main.cpp \
)

OBJS_DIR += srcs/server/ srcs/command/ srcs/utils/
DEPS_DIR += srcs/server/ srcs/command/ srcs/utils/
srcs += $(addprefix srcs/server/, \
		Server.cpp Client.cpp Reply.cpp Channel.cpp\
)

srcs += $(addprefix srcs/utils/,\
		Utils.cpp \
)

srcs += $(addprefix srcs/command/,\
		CAP.cpp NICK.cpp USER.cpp PONG.cpp MODE.cpp PASS.cpp\
		JOIN.cpp CommandUtils.cpp\
)

OBJS := $(srcs:%.cpp=objs/%.o)
DEPS := $(srcs:%.cpp=deps/%.d)

OBJS_DIR := $(addprefix objs/, $(OBJS_DIR))
OBJS_DIR := $(addsuffix .keep, $(OBJS_DIR))

DEPS_DIR := $(addprefix deps/, $(DEPS_DIR))
DEPS_DIR := $(addsuffix .keep, $(DEPS_DIR))

INC= inc

debugflags := -g3 -fsanitize=address
headerflags := -MMD -MP
CXXFLAGS := #-Wall -Werror -Wextra -std=c++98

############# basic rules ##############
.PHONY: all clean fclean re
all: $(NAME)

-include $(deps)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CYN)\n=====link=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(OBJS)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)$(NAME)$(RES)"
	@echo "$(CYN)==============$(RES)"

./objs/%.o: %.cpp $(OBJS_DIR) $(DEPS_DIR)
	@$(CXX) $(CXXFLAGS) -I$(INC) $(headerflags) -MF ./deps/$(*).d -c $< -o $@
	@echo "$< =========> $(GRN) $@ $(RES)"

$(OBJS_DIR):
	@mkdir -p $@
$(DEPS_DIR):
	@mkdir -p $@

clean:
	$(RM) $(OBJS)
	$(RM) $(deps)

fclean: clean
	$(RM) $(NAME)
	$(RM) ./objs
	$(RM) ./deps

re: fclean all

############## convenient rules ##############
.PHONY: debug leak
debug: CXXFLAGS += $(debugflags)
debug: re

run:
	./ircserv 8080 password

RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
