# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkling <mkling@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 14:56:12 by mkling            #+#    #+#              #
#    Updated: 2024/11/26 16:45:51 by mkling           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

MAIN		= main.c \

FUNC		= syntax.c monitor.c wait.c actions.c clean.c

SRCS		= $(FUNC) $(MAIN)

OBJS		= %.c: %.o

CC			= cc

CFLAGS		= -Wall -Wextra -Werror


all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

%.o:		%.c
			$(CC) $(CFLAGS) $(INC) -c $< -o $@

debug:		$(OBJS)
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(SRCS)

clean:
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re debug
