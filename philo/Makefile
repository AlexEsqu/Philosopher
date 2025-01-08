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

MAIN		= main.c

FUNC		= syntax.c monitor.c wait.c actions.c clean.c

SRC_DIR		= src

SRCS		= $(addprefix $(SRC_DIR)/, $(FUNC)) $(addprefix $(SRC_DIR)/, $(MAIN))

OBJ_DIR		= obj

OBJS		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC_DIR		= inc

INC			= -I$(INC_DIR)

CC			= cc

CFLAGS		= -Wall -Wextra -Werror


all:		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o  $@

$(OBJ_DIR):
			mkdir -p $@

debug:
			$(CC) $(CFLAGS) $(INC) -g3 -o $(NAME) $(SRCS)

clean:
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re debug
