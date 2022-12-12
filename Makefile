NAME := ircserv
CXXFLAGS := c++
RM := rm -rf

objs_dir += srcs/
deps_dir += srcs/
srcs += $(addprefix srcs/, \
    main.cpp \
)

objs_dir += srcs/server/
deps_dir += srcs/server/
srcs += $(addprefix srcs/server/, \
    Server.cpp\
		User.cpp\
    )

objs := $(srcs:%.cpp=objs/%.o)
deps := $(srcs:%.cpp=deps/%.d)

objs_dir := $(addprefix objs/, $(objs_dir))
objs_dir := $(addsuffix .keep, $(objs_dir))

deps_dir := $(addprefix deps/, $(deps_dir))
deps_dir := $(addsuffix .keep, $(deps_dir))

debugflags := -g3 -fsanitize=address
headerflags := -MMD -MP
CXXFLAGS := #-Wall -Werror -Wextra -std=c++98


############# basic rules ##############
.PHONY: all clean fclean re
all: $(NAME)

-include $(deps)

$(NAME): $(objs)
	$(CXX) $(CXXFLAGS) $(objs) -o $(NAME)

./objs/%.o: %.cpp $(objs_dir) $(deps_dir)
	$(CXX) $(CXXFLAGS) -Iinc $(headerflags) -MF ./deps/$(*).d -c $< -o $@

$(objs_dir):
	mkdir -p $@
$(deps_dir):
	mkdir -p $@

clean:
	$(RM) $(objs)
	$(RM) $(deps)

fclean: clean
	$(RM) $(NAME)

re: fclean all

############## convenient rules ##############
.PHONY: debug leak
debug: CXXFLAGS += $(debugflags)
debug: re

run:
	./ircserv 8080 password
