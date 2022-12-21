# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 20:13:06 by ergrigor          #+#    #+#              #
#    Updated: 2022/10/08 23:08:28 by ergrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC	=	cc

CFLAGS = -Wall -Wextra -Werror

ALL_SRCS = $(wildcard *.c)

BONUS_SRCS = $(wildcard ft_lst*.c)

SRCS = $(filter-out $(BONUS_SRCS), $(ALL_SRCS))

OBJS = $(patsubst %.c, %.o, $(SRCS))

BONUS_OBJS = $(patsubst %.c, %.o, $(BONUS_SRCS))

RM = rm -f

AR = ar rcs

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(NAME) $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus
