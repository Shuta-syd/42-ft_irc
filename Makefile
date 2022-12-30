NAME := ircserv
CXX := c++
RM := rm -rf

objs_dir += srcs/
deps_dir += srcs/
srcs += $(addprefix srcs/, \
    main.cpp \
)

objs_dir += srcs/server/ srcs/command/ srcs/utils/
deps_dir += srcs/server/ srcs/command/ srcs/utils/
srcs += $(addprefix srcs/server/, \
		Server.cpp Client.cpp Reply.cpp Channel.cpp Signal.cpp\
)

srcs += $(addprefix srcs/utils/,\
		Utils.cpp \
)

srcs += $(addprefix srcs/command/,\
		CAP.cpp NICK.cpp USER.cpp PONG.cpp MODE.cpp PASS.cpp\
		JOIN.cpp PRIVMSG.cpp QUIT.cpp NAMES.cpp TOPIC.cpp KICK.cpp\
		INVITE.cpp PART.cpp NOTICE.cpp\
)

objs := $(srcs:%.cpp=objs/%.o)
deps := $(srcs:%.cpp=deps/%.d)

objs_dir := $(addprefix objs/, $(objs_dir))
objs_dir := $(addsuffix .keep, $(objs_dir))

deps_dir := $(addprefix deps/, $(deps_dir))
deps_dir := $(addsuffix .keep, $(deps_dir))

INC= incs

debugflags := -g3 -fsanitize=address
headerflags := -MMD -MP
CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -pedantic
#CXXFLAGS := -std=c++17

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

./objs/%.o: %.cpp $(objs_dir) $(deps_dir)
	@$(CXX) $(CXXFLAGS)  -I$(INC) $(headerflags) -MF ./deps/$(*).d -c $< -o $@
	@echo "$< =========> $(GRN) $@ $(RES)"

$(objs_dir):
	@mkdir -p $@
$(deps_dir):
	@mkdir -p $@

clean:
	$(RM) $(objs)
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

run: all
	./ircserv 8080 password
RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
