NAME = minishell
INC = ./Includes/
LIBFT = ./libft/

LIB_LIBFT = $(LIBFT)/libft.a
CC = cc
OBJS_DIR = objs
SRCS_DIR = src
FLAGS =  -I $(INC) #-ggdb #-fsanitize=address
LINKERS = -lreadline -L$(LIBFT) -lft
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
RM = rm -rf
MKDIR = mkdir -p
.DEFAULT_GOAL = all

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJS_DIR):
	$(MKDIR) $(OBJS_DIR)
all: $(NAME)


$(NAME): $(LIB_LIBFT) $(OBJS) | $(OBJS_DIR)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LINKERS)

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
	@cd readline && ./configure && make 
#&& make install
push:
	@git add .
	@git commit -m "$m"
	@git push origin Ero

.PHONY: all clean fclean re bonus push readline
