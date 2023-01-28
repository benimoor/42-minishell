NAME = minishell
INC = ./Includes/
LIBFT = ./libft/

PREFIX = $(shell find ${HOME} -name readline_out 2>/dev/null)

LIB_LIBFT = $(LIBFT)/libft.a
CC = cc
OBJS_DIR = objs
SRCS_DIR = src
FLAGS =  -I $(INC) -I./readline/readline_out/include# -Wall -Wextra -Werror #-ggdb #-fsanitize=address
LINKERS = -L./readline/readline_out/lib -lreadline -ltinfo -L$(LIBFT) -lft
DIRS = $(shell find $(SRCS_DIR) -type d)

OBJS_DIRS = $(patsubst src/%, objs/%, $(DIRS))

SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

RM = rm -rf
MKDIR = mkdir -p
.DEFAULT_GOAL = all

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c 
	$(CC) $(FLAGS) -c $< -o $@



$(OBJS_DIR)/%: $(SRCS_DIR)/%
	$(MKDIR) $(OBJS_DIRS)

all: $(NAME)


rule:  $(OBJS_DIRS) $(OBJS)
	@echo $(DIRS)

$(NAME): $(LIB_LIBFT) $(OBJS_DIRS) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LINKERS) -o $(NAME)

$(LIB_LIBFT):
	make -C ./libft
bonus: all

clean:
	$(RM) $(OBJS_DIR)
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re: fclean all

readline:
	@cd readline && make clean && ./configure --prefix=$(PREFIX) && make && make install
#&& make install
push:
	@git add .
	@git commit -m "$m"
	@git push

.PHONY: all clean fclean re bonus push readline
